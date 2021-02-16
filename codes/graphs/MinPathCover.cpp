/* Author: Ubiratan Correia Barbosa Neto
 * Min Path Cover Implementation using Dinic
 */

int32_t main() {
  DESYNC;
  int n, m;
  cin >> n >> m;
  Dinic dinic(n + n);
  for (int i = 1; i <= n; i++) {
    dinic.add_to_src(i, 1);
    dinic.add_to_snk(i + n, 1);
  }

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    dinic.add_edge(u, v + n, 1);
  }

  dinic.calculate();
  for (int i = 1; i <= n; i++) {
    for (Dinic::FlowEdge e : dinic.adj[i]) {
      if (e.cap == 1 && e.c == 0 && 1 <= e.v && e.v - n <= n) {
        adj[i].pb(e.v - n);
        dg[e.v - n]++;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (dg[i] == 0) {
      paths.pb(vector<int>());
      go(i, paths.size() - 1);
    }
  }

  cout << paths.size() << endl;
  for (int i = 0; i < paths.size(); i++) {
    for (int v : paths[i]) cout << v << " ";
    cout << endl;
  }
}
