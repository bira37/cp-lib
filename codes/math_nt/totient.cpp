/* Author: Ubiratan Correia Barbosa Neto
 * Euler's Totient
 */

namespace NT {

const int MAX_TOT = 1123456;

int totient[MAX_TOT];

void EulerTotient(int n) {
  for (int i = 0; i <= n; i++) totient[i] = i;
  for (int p = 2; p <= n; p++) {
    if (totient[p] == p) {
      totient[p] = p - 1;
      for (int i = p + p; i <= n; i += p) {
        totient[i] = (totient[i] / p) * (p - 1);
      }
    }
  }
}

int SingleTotient(int x) {
  int ans = x;
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      while (x % i == 0) x /= i;
      ans -= ans / i;
    }
  }
  if (x > 1) ans -= ans / x;
  return ans;
}

};  // namespace NT
