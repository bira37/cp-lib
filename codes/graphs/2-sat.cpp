// I'm not the author
// Author: Vinicius Hirschle (viniciusth)
struct _2SAT {  // 1 based
  vector<vector<int>> g, gt;
  int n, n2;
  _2SAT() {}
  _2SAT(int n) : n(n) {  // literals range from [1 ... n]
    n2 = 2 * n;
    g = gt = vector<vector<int>>(n2 + 1, vector<int>());
  }
  int neg(int a) { return a + n * (a > n ? -1 : 1); }
  void add(int a, int b) {
    // -x is negation of x
    if (a < 0) a = -a + n;
    if (b < 0) b = -b + n;
    // adding clause a v b is equal to adding -a -> b and -b -> a
    g[neg(a)].pb(b);
    gt[b].pb(neg(a));
    g[neg(b)].pb(a);
    gt[a].pb(neg(b));
  }
  vector<int> solve() {
    vector<int> used(n2 + 1), comp(n2 + 1, -1), res(n), order;
    function<void(int)> dfs1 = [&](int u) {
      used[u] = 1;
      for (int v : g[u])
        if (!used[v]) dfs1(v);
      order.push_back(u);
    };
    function<void(int, int)> dfs2 = [&](int u, int group) {
      comp[u] = group;
      for (int v : gt[u])
        if (comp[v] == -1) dfs2(v, group);
    };
    for (int i = 1; i <= n2; i++)
      if (!used[i]) dfs1(i);
    for (int i = n2 - 1, j = 0; i >= 0; i--)
      if (comp[order[i]] == -1) dfs2(order[i], j++);
    for (int i = 1; i <= n; i++) {
      if (comp[i] == comp[neg(i)]) {
        res.clear();
        return res;  // impossible
      }
      res[i - 1] = comp[i] > comp[neg(i)];
    }
    return res;
  }
};
