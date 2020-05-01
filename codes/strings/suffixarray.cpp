/* Author: Ubiratan Correia Barbosa Neto
 * Suffix Array
 */

/* Suffix Array using Counting Sort Implementation */
/* rnk is inverse of sa array */
/* aux arrays are needed for sorting step */
/* inverse sorting (using rotating arrays and blocks of power of 2) */
/* rmq data structure needed for calculating lcp of two non adjacent suffixes
 * sorted */

struct SuffixArray {
  vector<int> rnk, tmp, sa, sa_aux, lcp, pot, sp[22];

  int block, n;

  string s;

  SuffixArray() {}

  SuffixArray(string t) {
    s = t;
    n = t.size();
    rnk.resize(n + 1);
    for (int i = 0; i < 22; i++) sp[i].resize(n + 1);
    pot.resize(n + 1);
    tmp.resize(max(257LL, n + 1));
    sa.resize(n + 1);
    sa_aux.resize(n + 1);
    lcp.resize(n + 1);
    block = 0;
  }

  bool suffixcmp(int i, int j) {
    if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    i += block, j += block;
    i %= n;
    j %= n;
    return rnk[i] < rnk[j];
  }

  void suffixSort(int MAX_VAL) {
    for (int i = 0; i <= MAX_VAL; i++) tmp[i] = 0;
    for (int i = 0; i < n; i++) tmp[rnk[i]]++;
    for (int i = 1; i <= MAX_VAL; i++) tmp[i] += tmp[i - 1];
    for (int i = n - 1; i >= 0; i--) {
      int aux = sa[i] - block;
      aux %= n;
      if (aux < 0) aux += n;
      sa_aux[--tmp[rnk[aux]]] = aux;
    }
    for (int i = 0; i < n; i++) sa[i] = sa_aux[i];
    tmp[0] = 0;
    for (int i = 1; i < n; i++)
      tmp[i] = tmp[i - 1] + suffixcmp(sa[i - 1], sa[i]);
    for (int i = 0; i < n; i++) rnk[sa[i]] = tmp[i];
  }

  void calculate() {
    s += '\0';
    n++;
    for (int i = 0; i < n; i++) {
      sa[i] = i;
      rnk[i] = s[i];
      tmp[i] = 0;
    }
    suffixSort(256);
    block = 1;
    while (tmp[n - 1] != n - 1) {
      suffixSort(tmp[n - 1]);
      block *= 2;
    }
    for (int i = 0; i < n - 1; i++) sa[i] = sa[i + 1];
    n--;
    tmp[0] = 0;
    for (int i = 1; i < n; i++)
      tmp[i] = tmp[i - 1] + suffixcmp(sa[i - 1], sa[i]);
    for (int i = 0; i < n; i++) rnk[sa[i]] = tmp[i];
    s.pop_back();
    sa.pop_back();
  }

  void calculate_lcp() {
    int last = 0;
    for (int i = 0; i < n; i++) {
      if (rnk[i] == n - 1) continue;
      int x = rnk[i];
      lcp[x] = max(0LL, last - 1);
      while (sa[x] + lcp[x] < n && sa[x + 1] + lcp[x] < n &&
             s[sa[x] + lcp[x]] == s[sa[x + 1] + lcp[x]]) {
        lcp[x]++;
      }
      last = lcp[x];
    }
  }

  void build_lcp_table() {
    int k = 0;
    for (int j = 0; (1 << j) <= 2 * n; j++) {
      for (; k <= n && k < (1 << j); k++) {
        pot[k] = j - 1;
      }
    }
    for (int i = 0; i < n; i++) {
      sp[0][i] = lcp[i];
    }
    for (int i = 1; (1 << i) <= n; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int query_lcp(int x, int y) {
    if (x == y) return n - x;
    if (rnk[x] > rnk[y]) swap(x, y);
    int l = rnk[x], r = rnk[y] - 1;
    return min(sp[pot[r - l + 1]][l],
               sp[pot[r - l + 1]][r - (1LL << pot[r - l + 1]) + 1]);
  }

  int number_of_substrings() {
    int ans = n - sa[0];
    for (int i = 0; i < n - 1; i++) {
      int length = n - sa[i + 1];
      ans += length - lcp[i];
    }
    return ans;
  }
};
