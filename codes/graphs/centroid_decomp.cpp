/* Author: Ubiratan Correia Barbosa Neto
 */

/* Centroid Decomposition Implementation */
/* c_p[] contains the centroid predecessor on centroid tree */
/* removed[] says if the node was already selected as a centroid (limit the
 * subtree search) */
/* L[] contains the height of the vertex (from root) on centroid tree (Max is
 * logN) */
/* N is equal to the maximum size of tree (given by statement) */

struct CentroidDecomposition {
  vector<bool> removed;
  vector<int> L, subsz;
  vector<int> c_p;
  vector<vector<int>> adj;

  CentroidDecomposition() {}

  CentroidDecomposition(int n) {
    removed.resize(n + 1);
    L.resize(n + 1);
    c_p.resize(n + 1);
    subsz.resize(n + 1);
    adj.resize(n + 1, vector<int>());
    for (int i = 0; i < n + 1; i++) {
      c_p[i] = -1;
    }
  }

  void centroid_subsz(int u, int p) {
    subsz[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (v == p || removed[v]) continue;
      centroid_subsz(v, u);
      subsz[u] += subsz[v];
    }
  }

  int find_centroid(int u, int p, int sub) {
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (v == p || removed[v]) continue;
      if (subsz[v] > subsz[sub] / 2) {
        return find_centroid(v, u, sub);
      }
    }
    return u;
  }

  void decompose(int u = 1, int p = -1, int r = 0) {
    centroid_subsz(u, -1);
    int centroid = find_centroid(u, -1, u);
    L[centroid] = r;
    c_p[centroid] = p;
    removed[centroid] = true;

    process(centroid, p);

    for (int i = 0; i < adj[centroid].size(); i++) {
      int v = adj[centroid][i];
      if (removed[v]) continue;
      decompose(v, centroid, r + 1);
    }
  }

  void process(int u, int p) {
    // do something here to process subtree
  }
};
