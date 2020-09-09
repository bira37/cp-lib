/* Author: Ubiratan Neto */
/* DSU to check bipartite properties on graphs */

int uf[312345], d[312345], sz[312345];

void init(int n) {
  for (int i = 0; i <= n; i++) {
    uf[i] = i;
    sz[i] = 1;
    d[i] = 0;
  }
}

ii get(int x) {
  if (uf[x] == x) {
    return ii(x, 0);
  }
  ii ans = get(uf[x]);
  d[x] = d[x] + ans.ss;
  uf[x] = ans.ff;
  return ii(uf[x], d[x]);
}

bool merge(int a, int b) {
  auto x = get(a), y = get(b);
  if (x.ff == y.ff) return false;
  if (sz[x.ff] < sz[y.ff]) swap(x, y);
  uf[y.ff] = x.ff;
  sz[x.ff] += sz[y.ff];
  d[y.ff] = y.ss + x.ss + 1;
  return true;
}
