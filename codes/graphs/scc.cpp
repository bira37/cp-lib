/* Author: Ubiratan Correia Barbosa Neto
 * Kosaraju Strongly Connected Components
 */

struct SCC {
  vector<vector<int> > adj_t;
  vector<vector<int> > scc_adj;
  int comp;
  vector<bool> vis;
  vector<int> scc;
  stack<int> vertex;

  SCC() {}

  SCC(int n) {
    adj_t.resize(n + 1, vector<int>());
    scc_adj.resize(n + 1, vector<int>());
    comp = 0;
    vis.resize(n + 1);
    scc.resize(n + 1);
  }

  void dfs(int u) {
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!vis[v]) dfs(v);
    }
    vertex.push(u);
  }

  void dfst(int u, int comp) {
    scc[u] = comp;
    vis[u] = true;
    for (int i = 0; i < adj_t[u].size(); i++) {
      int v = adj_t[u][i];
      if (!vis[v]) dfst(v, comp);
    }
  }

  void calculate() {
    int n = vis.size() - 1;

    for (int i = 0; i <= n; i++) {
      vis[i] = false;
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        dfs(i);
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int v : adj[i]) {
        adj_t[v].pb(i);
      }
    }

    for (int i = 1; i <= n; i++) {
      vis[i] = false;
    }

    while (!vertex.empty()) {
      if (!vis[vertex.top()]) {
        comp++;
        dfst(vertex.top(), comp);
      }
      vertex.pop();
    }

    // set< ii > edge_check; //eliminates duplicate edges (additional O(logn))

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < adj[i].size(); j++) {
        int v = adj[i][j];
        if (scc[i] == scc[v]) continue;
        // if(edge_check.count(ii(scc[i], scc[v]))) continue; //eliminates
        // duplicate edges (additional O(logn))
        scc_adj[scc[i]].push_back(scc[v]);
        // edge_check.insert(ii(scc[i], scc[v])); //eliminates duplicate edges
        // (additional O(logn))
      }
    }
  }
};
