
template <class NumT = int> struct Edge {
  int a, b;
  NumT w;
  Edge(int _a, int _b) : a(_a), b(_b), w(1) {}
  Edge(int _a, int _b, NumT _w) : a(_a), b(_b), w(_w) {}
};
template <class NumT = int> struct Flow {
  int size, source, sink;
  vector<vector<NumT> > adj;
  vector<Edge<NumT> > e;
  vector<bool> visited; // used for bfs/dfs
  vector<int> dist;     // used for layered graph / dinic's
  vector<int> used;     // edges used in dinic's blocking flow
  Flow(int sz) : size(sz) {
    adj = vector<vector<NumT> >(sz);
    source = sz-1, sink = sz-2;
  }
  void setup(const int s, const int t) {
    source = s;
    sink = t;
  }
  void add_edge(const int u, const int v, const NumT weight) {
    adj[u].push_back(e.size());
    e.push_back(Edge<NumT>(u, v, weight));
    adj[v].push_back(e.size());
    e.push_back(Edge<NumT>(v, u, 0));
  }
  bool layered_bfs() {
    dist.assign(size, -1);
    dist[source] = 0;
    vector<int> q;
    q.push_back(source);
    for (int i = 0; i < q.size(); i++) {
      if (dist[sink] != -1) break;
      int u = q[i];
      for (int x : adj[u]) {
        if (dist[e[x].b] == -1 && e[x].w > 0) {
          dist[e[x].b] = dist[u] + 1;
          q.push_back(e[x].b);
        }
      }
    }
    return dist[sink] != -1;
  }
  NumT augmenting(const int u, const NumT bottle) {
    if (!bottle) return 0;
    if (u == sink) return bottle;
    for (int& i = used[u]; i < adj[u].size(); i++) {
      int x = adj[u][i];
      if (dist[e[x].b] != dist[u] + 1) continue; // only use edges of layered graph
      NumT cf = augmenting(e[x].b, min(bottle, e[x].w));
      e[x].w -= cf;
      e[x ^ 1].w += cf;
      if (cf) return cf;
    }
    return 0;
  }
  NumT blocking_flow() {
    if (!layered_bfs()) return 0;
    used.assign(size, 0);
    NumT aug, flow = 0;
    while ((aug = augmenting(source, numeric_limits<NumT>::max()))) flow += aug;
    return flow;
  }
  NumT maxflow() {
    NumT aug, flow = 0;
    while ((aug = blocking_flow())) flow += aug;
    return flow;
  }
};
