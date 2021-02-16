/* Author: Ubiratan Correia Barbosa Neto
 * Floyd Warshall
 */

struct FloydWarshall {
  vector<vector<vector<int> > > dist;

  FloydWarshall() {}

  FloydWarshall(int n) {
    dist.resize(n + 1, vector<vector<int> >(n + 1, vector<int>(n + 1)));
  }

  void relax(int i, int j, int k) {
    dist[k][i][j] =
        min(dist[k - 1][i][j], dist[k - 1][i][k] + dist[k - 1][k][j]);
  }

  void calculate() {
    for (int k = 0; k < dist.size(); k++) {
      for (int i = 1; i < dist.size(); i++) {
        for (int j = 1; j < dist.size(); j++) {
          if (i == j)
            dist[k][i][j] = 0;
          else
            dist[k][i][j] = INF;
        }
      }
    }
    for (int k = 1; k < dist.size(); k++) {
      for (int i = 1; i < dist.size(); i++) {
        for (int j = 1; j < dist.size(); j++) {
          relax(i, j, k);
        }
      }
    }
  }
};
