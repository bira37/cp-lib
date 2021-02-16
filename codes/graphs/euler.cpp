/* Author: Ubiratan Correia Barbosa Neto
 * Eulerian Path / Circuit
 * REMEMBER TO CHECK IF PATH/CIRCUIT HAS THE DESIRED SIZE (OR COVER ALL VERTEX)
 */

struct EulerianCircuit {
  vector<vector<int>> g;
  vector<vector<int>> back_ref;
  vector<int> walk;
  vector<int> deg, indeg, outdeg;
  bool directed;

  EulerianCircuit(int n, bool directed) : directed(directed) {
    if (directed) {
      indeg.resize(n + 1, 0);
      outdeg.resize(n + 1, 0);
    } else {
      deg.resize(n + 1, 0);
      back_ref.resize(n + 1);
    }
    g.resize(n + 1);
  }

  void add_directed_edge(int u, int v) {
    outdeg[u]++;
    indeg[v]++;
    g[u].pb(v);
  }

  void add_undirected_edge(int u, int v) {
    deg[u]++;
    deg[v]++;
    g[u].pb(v);
    g[v].pb(u);
    if (u != v) {
      int ref_u = g[v].size() - 1;
      int ref_v = g[u].size() - 1;
      back_ref[u].pb(ref_u);
      back_ref[v].pb(ref_v);
    } else {
      int cur = back_ref[u].size();
      back_ref[u].pb(cur + 1);
      back_ref[u].pb(cur);
    }
  }

  void add_edge(int u, int v) {
    if (directed)
      add_directed_edge(u, v);
    else
      add_undirected_edge(u, v);
  }

  void undirected_euler(int u) {
    while (g[u].size() > 0) {
      if (g[u].back() < 0) {
        g[u].pop_back();
        back_ref[u].pop_back();
        continue;
      }
      int v = g[u].back();
      int ref = back_ref[u].back();
      g[u].pop_back();
      back_ref[u].pop_back();

      if (g[v].size() > ref) g[v][ref] = -1;

      undirected_euler(v);
    }
    walk.push_back(u);
  }

  void directed_euler(int u) {
    while (g[u].size() > 0) {
      int v = g[u].back();

      g[u].pop_back();

      directed_euler(v);
    }

    walk.push_back(u);
  }
  bool process_directed_euler(bool path = false, int root = 1) {
    int inp = -1, out = -1;
    if (path) {
      for (int i = 1; i < g.size(); i++) {
        if (outdeg[i] - indeg[i] == 1) {
          if (out != -1) return false;
          out = i;
        }
        if (indeg[i] - outdeg[i] == 1) {
          if (inp != -1) return false;
          inp = i;
        }
      }
      if (inp == -1 || out == -1) return false;
      add_directed_edge(inp, out);
      directed_euler(inp);
      walk.pop_back();
      return true;
    } else {
      for (int i = 1; i < g.size(); i++) {
        if (indeg[i] != outdeg[i]) return false;
      }
      directed_euler(root);
      return true;
    }
  }

  bool process_undirected_euler(bool path = false, int root = 1) {
    vector<int> odds;
    if (path) {
      for (int i = 1; i < g.size(); i++) {
        if (deg[i] % 2) odds.push_back(i);
      }
      if (odds.size() != 2) return false;
      add_undirected_edge(odds[0], odds[1]);
      undirected_euler(odds[0]);
      walk.pop_back();
      return true;
    } else {
      for (int i = 1; i < g.size(); i++) {
        if (deg[i] % 2) return false;
      }
      undirected_euler(root);
      return true;
    }
  }

  bool calculate(bool path = false, int root = 1) {
    if (directed) {
      return process_directed_euler(path, root);
    } else {
      return process_undirected_euler(path, root);
    }
  }
};
