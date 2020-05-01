/* Author: Ubiratan Correia Barbosa Neto
 * Lowest Common Ancestor
 */

struct LCA {
  int tempo;
  vector<int> st, ed, dad, anc[20], L;
  vector<bool> vis;

  LCA() {}

  LCA(int n) {
    tempo = 0;
    st.resize(n + 1);
    ed.resize(n + 1);
    dad.resize(n + 1);
    L.resize(n + 1);
    for (int i = 0; i < 20; i++) anc[i].resize(n + 1);
    vis.resize(n + 1);
    for (int i = 0; i <= n; i++) vis[i] = false;
  }

  void dfs(int u) {
    vis[u] = true;
    st[u] = tempo++;
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!vis[v]) {
        dad[v] = u;
        L[v] = L[u] + 1;
        dfs(v);
      }
    }
    ed[u] = tempo++;
  }

  bool is_ancestor(int u, int v) { return st[u] <= st[v] && st[v] <= ed[u]; }

  int query(int u, int v) {
    if (is_ancestor(u, v)) return u;
    for (int i = 19; i >= 0; i--) {
      if (anc[i][u] == -1) continue;
      if (!is_ancestor(anc[i][u], v)) u = anc[i][u];
    }
    return dad[u];
  }

  int distance(int u, int v) { return L[u] + L[v] - 2 * L[query(u, v)]; }

  void precalculate() {
    dad[1] = -1;
    L[1] = 0;
    dfs(1);
    for (int i = 1; i < st.size(); i++) {
      anc[0][i] = dad[i];
    }
    for (int i = 1; i < 20; i++) {
      for (int j = 1; j < st.size(); j++) {
        if (anc[i - 1][j] != -1) {
          anc[i][j] = anc[i - 1][anc[i - 1][j]];
        } else {
          anc[i][j] = -1;
        }
      }
    }
  }
};
