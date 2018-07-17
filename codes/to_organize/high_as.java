import java.util.*;
import java.io.*;

class high_as {
    Scanner in;
    PrintWriter out;

    public void solve() throws IOException {
        int n = in.nextInt();
        String[] names = new String[n];
        int[] win = new int[n];
        for (int i = 0; i < n; i++) {
            names[i] = in.next();
            win[i] = in.nextInt();
        }
        int[][] p = new int[n][n];
        int[] rem = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                p[i][j] = in.nextInt();
                rem[i] += p[i][j];
                if (j < i) {
                    assert p[i][j] == p[j][i];
                }
                if (j == i) {
                    assert p[i][j] == 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            Graph g = new Graph(n * n + n + 2);
            int src = n * n + n;
            int dst = n * n + n + 1;

            int srcSum = 0;
            for (int j = 0; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (j != i && k != i) {
                        g.addEdge(src, j * n + k, p[j][k]);
                        srcSum += p[j][k];
                        g.addEdge(j * n + k, n * n + j, p[j][k]);
                        g.addEdge(j * n + k, n * n + k, p[j][k]);
                    }
                }
            }

            boolean canWin = true;
            boolean[] subSet = new boolean[n];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int can = win[i] + rem[i] - win[j];
                    if (can < 0) {
                        canWin = false;
                        subSet[j] = true;
                        break;
                    }
                    g.addEdge(n * n + j, dst, can);
                }
            }

            if (canWin) {
                int v = (int) g.maxFlow(src, dst);
                if (v != srcSum) {
                    canWin = false;
                    g.dfs(src);
                    for (int j = 0; j < n; j++) {
                        if (i != j && g.u[n * n + j]) {
                            subSet[j] = true;
                        }
                    }
                }
            }

            if (canWin) {
                out.println(names[i] + " can win");
            } else {
                out.println(names[i] + " cannot win because of the following teams:");
                out.print("  ");
                boolean first = true;
                for (int j = 0; j < n; j++) {
                    if (subSet[j]) {
                        if (!first) {
                            out.print(", ");
                        }
                        first = false;
                        out.print(names[j]);
                    }
                }
                out.println();
            }
        }
    }

    class Graph {
        int n;
        Vertex[] vs;
        boolean[] u;

        LinkedList<Vertex>[] q;
        int[] cnt;
        private int qmin;

        @SuppressWarnings("unchecked")
        Graph(int n) {
            this.n = n;
            vs = new Vertex[n];
            u = new boolean[n];
            for (int i = 0; i < n; i++) {
                vs[i] = new Vertex(i);
            }
        }

        void addEdge(int s, int t, int c) {
            Edge ef = new Edge(vs[s], vs[t], c);
            Edge er = new Edge(vs[t], vs[s], 0);
            ef.r = er;
            er.r = ef;
            vs[s].edges.add(ef);
            vs[t].edges.add(er);
        }

        void dfs(int v) {
            u[v] = true;
            for (Edge e : vs[v].edges) {
                if (e.f < e.c && !u[e.d.ind]) {
                    dfs(e.d.ind);
                }
            }
        }

        @SuppressWarnings("unchecked")
        long maxFlow(int s, int t) {
            vs[s].h = n;

            for (int i = 0; i < n; i++) {
                vs[i].internal = i != s && i != t;
            }

            for (Edge e : vs[s].edges) {
                e.d.exc += e.c;
                e.f = e.c;
                e.r.f = -e.f;
            }

            q = new LinkedList[2 * n];
            for (int i = 0; i < 2 * n; i++) {
                q[i] = new LinkedList<Vertex>();
            }
            cnt = new int[2 * n];
            cnt[n] = 1;
            cnt[0] = n - 1;

            for (int i = 0; i < n; i++) {
                if (i != s && i != t) {
                    q[0].add(vs[i]);
                }
            }

            qmin = 0;
            int gap = n;
            while (qmin < gap) {
                int level = qmin;
                for (Iterator<Vertex> it = q[level].iterator(); it.hasNext();) {
                    Vertex v = it.next();
//                    System.out.println(v.ind + " " + v.exc + " " + v.h);
                    if (v.discharge()) {
                        it.remove();
                        q[v.h].add(v);
                        if (cnt[level] == 0) {
                            gap = level;
                        }

                        break;
                    } else {
                        it.remove();
                    }
                    if (qmin != level) {
                        break;
                    }
                }
                while (qmin < gap && q[qmin].size() == 0) {
                    qmin++;
                }
            }

            return vs[t].exc;
        }

        class Edge {
            Vertex s;
            Vertex d;
            long c;
            long f;
            Edge r;

            Edge(Vertex s, Vertex d, long c) {
                this.s = s;
                this.d = d;
                this.c = c;
            }

            public String toString() {
                return s.ind + "->" + d.ind + " (" + f + "/" + c + ")";
            }
        }

        class Vertex {
            int ind;
            ArrayList<Edge> edges;
            long exc;
            int h;
            int cur;
            boolean internal;

            Vertex(int ind) {
                this.ind = ind;
                edges = new ArrayList<Edge>();
                cur = 0;
            }

            void lift() {
                int newH = Integer.MAX_VALUE;
                for (Edge e : edges) {
                    if (e.c > e.f) {
                        newH = Math.min(newH, e.d.h + 1);
                    }
                }
                cnt[h]--;
                h = newH;
                cnt[h]++;

            }

            boolean discharge() {
                while (exc > 0 && cur < edges.size()) {
                    Edge e = edges.get(cur);
                    if (e.c > e.f && e.d.h < h) {
                        long delta = Math.min(e.c - e.f, exc);
                        e.f += delta;
                        e.r.f -= delta;
                        exc -= delta;
                        e.d.exc += delta;
                        if (e.d.exc == delta && e.d.internal) {
                            q[e.d.h].add(e.d);
                            qmin = e.d.h;
                        }
                    }
                    cur++;
                }

                if (exc == 0) {
                    return false;
                }

                lift();
                cur = 0;
                return true;
            }
        }
    }

    public void run() {
        try {
            in = new Scanner(new File("high.in"));
            out = new PrintWriter(new File("high.out"));

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] arg) {
        new high_as().run();
    }
}
