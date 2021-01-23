/* Author: Ubiratan Correia Barbosa Neto
 * Longest Increasing Subsequence
 */
/* Use upper_bound to swap to longest non decreasing subsequence */

struct LIS {
  vector<int> seq;
  vector<ii> pointer;
  int sz;
  LIS() {}

  LIS(int n) {
    seq.resize(n + 1);
    pointer.resize(n);
  }

  void calculate(vector<int>& v) {
    int n = v.size();
    vector<int> aux(n + 1);
    for (int i = 1; i <= n; i++) {
      seq[i] = INT_MAX;
      aux[i] = -1;
    }
    seq[0] = INT_MIN;
    aux[0] = -1;
    for (int i = 0; i < n; i++) {
      int index = lower_bound(seq.begin(), seq.end(), v[i]) - seq.begin();
      index--;
      if (seq[index + 1] > v[i]) {
        seq[index + 1] = min(seq[index + 1], v[i]);
        aux[index + 1] = i;
      }
      pointer[i] = ii(index + 1, aux[index]);
    }
    for (int i = n; i >= 0; i--) {
      if (seq[i] != INT_MAX) {
        sz = i;
        break;
      }
    }
  }
};
