/* Author: Ubiratan Neto
 *
 */

struct BIT2D {
  vector<vector<int> > bit;

  int n, m;

  BIT2D() {}

  BIT2D(int n, int m) {
    bit.resize(n + 1, vector<int>(m + 1));
    this->n = n;
    this->m = m;
  }

  void update(int x, int y, int val) {
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        bit[i][j] += val;
      }
    }
  }

  int prefix_query(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        ans += bit[i][j];
      }
    }
    return ans;
  }

  int query(int x1, int y1, int x2, int y2) {
    return prefix_query(x2, y2) + prefix_query(x1 - 1, y1 - 1) -
           prefix_query(x2, y1 - 1) - prefix_query(x1 - 1, y2);
  }
};
