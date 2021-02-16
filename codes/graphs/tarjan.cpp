/* Author: Ubiratan Correia Barbosa Neto
 * Tarjan Bridges + Articulations
 */

struct Tarjan {
  int cont = 0;
  vector<int> st;
  vector<int> low;
  vector<ii> bridges;
  vector<bool> isArticulation;

  Tarjan() {}

  Tarjan(int n) {
    st.resize(n + 1);
    low.resize(n + 1);
    isArticulation.resize(n + 1);
    cont = 0;
    bridges.clear();
  }

  void calculate(int u, int p = -1) {
    st[u] = low[u] = ++cont;
    int son = 0;
    for (int i = 0; i < adj[u].size(); i++) {
      if (adj[u][i] == p) {
        p = 0;
        continue;
      }
      if (!st[adj[u][i]]) {
        calculate(adj[u][i], u);
        low[u] = min(low[u], low[adj[u][i]]);
        if (low[adj[u][i]] >= st[u])
          isArticulation[u] = true;  // check articulation

        if (low[adj[u][i]] > st[u]) {  // check if its a bridge
          bridges.push_back(ii(u, adj[u][i]));
        }

        son++;
      } else
        low[u] = min(low[u], st[adj[u][i]]);
    }

    if (p == -1) {
      if (son > 1)
        isArticulation[u] = true;
      else
        isArticulation[u] = false;
    }
  }
};
