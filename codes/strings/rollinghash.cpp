/* Author: Ubiratan Correia Barbosa Neto
 * Rolling Hash
 */

namespace Hash {

int B1, B2, M1, M2;

void init() {
  B1 = rand() % 65536;
  B2 = rand() % 65536;
  M1 = 1000000007;
  M2 = 1000000009;
}

struct RollingHash {
  vector<ii> hash;
  vector<ii> base;

  RollingHash() {}

  void calculate(string s) {
    int n = s.size();
    hash.resize(n + 1);
    base.resize(n + 1);
    base[0] = ii(1, 1);
    hash[0] = ii(0, 0);
    for (int i = 1; i <= n; i++) {
      int val = (int)(s[i - 1]);
      base[i] = ii(mod(base[i - 1].ff * B1, M1), mod(base[i - 1].ss * B2, M2));
      hash[i] = ii(mod(hash[i - 1].ff * B1 + val, M1),
                   mod(hash[i - 1].ss * B2 + val, M2));
    }
  }

  ii query(int l, int r) {
    ii ret;
    ret.ff = mod(hash[r].ff - hash[l - 1].ff * base[r - l + 1].ff, M1);
    ret.ss = mod(hash[r].ss - hash[l - 1].ss * base[r - l + 1].ss, M2);
    return ret;
  }
};

}  // namespace Hash
