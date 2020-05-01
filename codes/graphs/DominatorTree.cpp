/*
 * Dominator Trees
 */

template <typename T = int>
struct LinkDsu {
  vector<int> r;
  vector<T> best;
  LinkDsu(int n = 0) {
    r = vector<int>(n);
    iota(r.begin(), r.end(), 0);
    best = vector<T>(n);
  }

  int find(int u) {
    if (r[u] == u)
      return u;
    else {
      int v = find(r[u]);
      if (best[r[u]] < best[u]) best[u] = best[r[u]];
      return r[u] = v;
    }
  }

  T eval(int u) {
    find(u);
    return best[u];
  }
  void link(int p, int u) { r[u] = p; }
  void set(int u, T x) { best[u] = x; }
};

struct DominatorTree {
  typedef vector<vector<int>> Graph;
  vector<int> semi, dom, parent, st, from;
  Graph succ, pred, bucket;
  int r, n, tempo;

  void dfs(int u, int p) {
    semi[u] = u;
    from[st[u] = tempo++] = u;
    parent[u] = p;
    for (int v : succ[u]) {
      pred[v].push_back(u);
      if (semi[v] == -1) {
        dfs(v, u);
      }
    }
  }

  void build() {
    n = succ.size();
    dom.assign(n, -1);
    semi.assign(n, -1);
    parent.assign(n, -1);
    st.assign(n, 0);
    from.assign(n, -1);
    pred = Graph(n, vector<int>());
    bucket = Graph(n, vector<int>());
    LinkDsu<pair<int, int>> dsu(n);
    tempo = 0;

    dfs(r, r);
    for (int i = 0; i < n; i++) dsu.set(i, make_pair(st[i], i));

    for (int i = tempo - 1; i; i--) {
      int u = from[i];
      for (int v : pred[u]) {
        int w = dsu.eval(v).second;
        if (st[semi[w]] < st[semi[u]]) {
          semi[u] = semi[w];
        }
      }
      dsu.set(u, make_pair(st[semi[u]], u));
      bucket[semi[u]].push_back(u);
      dsu.link(parent[u], u);
      for (int v : bucket[parent[u]]) {
        int w = dsu.eval(v).second;
        dom[v] = semi[w] == parent[u] ? parent[u] : w;
      }
      bucket[parent[u]].clear();
    }
    for (int i = 1; i < tempo; i++) {
      int u = from[i];
      if (dom[u] != semi[u]) dom[u] = dom[dom[u]];
    }
  }

  DominatorTree(const Graph& g, int s) : succ(g), r(s) { build(); }
};
