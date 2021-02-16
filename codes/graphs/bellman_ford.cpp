/* Author: Ubiratan Correia Barbosa Neto
 * Bellman Ford
 */

struct BellmanFord {
  struct edges {
    int u, v, weight;
    edges(int u, int v, int weight) : u(u), v(v), weight(weight) {}
  };

  vector<int> dist;

  bool cycle = false;

  BellmanFord() {}

  BellmanFord(int n) { dist.resize(n + 1); }

  void calculate(int source) {
    for (int i = 0; i < dist.size(); i++) {
      dist[i] = INF;
    }
    dist[source] = 0;
    for (int k = 0; k < dist.size() - 1; k++) {
      for (int i = 0; i < e.size(); i++) {
        if (dist[e[i].v] > dist[e[i].u] + e[i].weight) {
          dist[e[i].v] = dist[e[i].u] + e[i].weight;
        }
      }
    }
    for (int i = 0; i < e.size(); i++) {
      if (dist[e[i].v] > dist[e[i].u] + e[i].weight) {
        cycle = true;
      }
    }
  }
};
