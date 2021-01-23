/* Author: Ubiratan Neto
 * Generic Sparse Table
 */

struct SparseTable {
  int MAXN, LOGN;
  vector<vector<int>> spt;
  vector<int> e;
  function<int(int, int)> merge_fn;

  SparseTable(vector<int>& v, function<int(int, int)> fn) {
    int n = v.size();
    MAXN = n;
    LOGN = 0;
    merge_fn = fn;
    while (n > 0) {
      LOGN++;
      n /= 2LL;
    }
    spt.resize(MAXN + 1, vector<int>(LOGN, 0));
    e.resize(MAXN + 1);
    _build(v);
  }

  void _build(vector<int>& a) {
    for (int i = 0; i < MAXN; i++) {
      spt[i][0] = a[i];
    }

    for (int i = 1; (1 << i) <= MAXN; i++) {
      for (int j = 0; j + (1 << i) <= MAXN; j++) {
        spt[j][i] = merge_fn(spt[j][i - 1], spt[j + (1 << (i - 1))][i - 1]);
      }
    }

    int k = 0;
    for (int j = 0; (1 << j) <= 2 * MAXN; j++) {
      for (; k <= MAXN && k < (1 << j); k++) {
        e[k] = j - 1;
      }
    }
  }

  int query(int l, int r) {
    assert(r < MAXN && l >= 0 && l <= r);
    int sz = r - l + 1;
    return merge_fn(spt[l][e[sz]], spt[r - (1 << e[sz]) + 1][e[sz]]);
  }
};