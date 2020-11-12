namespace NT {
/* Interpolates a polynomial of degree N-1 given N point-value pairs (x,y) and
 * returns f(k) */
/* Uses modular arithmetic */
int Interpolate(const vector<ii>& v, int k) {
  int ans = 0;
  int n = v.size();
  for (int i = 0; i < n; i++) {
    int num = v[i].ss;
    int den = 1;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      num = mod(num * (k - v[j].ff));
      den = mod(den * (v[i].ff - v[j].ff));
    }
    ans = mod(ans + divp(num, den));
  }
  return ans;
}

/* Fast version of Lagrange interpolation in linear time
 * Works when the set of given N points is a contiguous sequence from x = 1..n
 * Uses modular arithmetic
 */
int FastInterpolate(const vector<int>& v, int k) {
  int ans = 0;
  int n = v.size();
  int fat[n + 1];
  int ifat[n + 1];
  fat[0] = 1;
  ifat[0] = 1;
  for (int i = 1; i <= n; i++) {
    fat[i] = mod(fat[i - 1] * i);
    ifat[i] = exp(fat[i], M - 2);
  }

  int pref[n + 1];
  int suf[n + 2];
  pref[0] = 1;
  suf[n + 1] = 1;
  for (int i = 1; i <= n; i++) {
    pref[i] = mod(pref[i - 1] * (k - i));
  }
  for (int i = n; i >= 1; i--) {
    suf[i] = mod(suf[i + 1] * (k - i));
  }

  for (int i = 1; i <= n; i++) {
    int num = mod(pref[i - 1] * suf[i + 1]);
    num = mod(num * v[i - 1]);
    int den = mod(ifat[n - i] * ifat[i - 1]);
    if ((n - i) % 2) den = -den;
    ans = mod(ans + mod(num * den));
  }
  return ans;
}
}  // namespace NT
