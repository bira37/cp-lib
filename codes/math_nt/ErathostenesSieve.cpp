/* Author: Ubiratan Correia Barbosa Neto
 * Erasthostenes Sieve Implementation + Euler's Totient
 */

/* Calculate primes from 2 to N */
/* lf[i] stores the lowest prime factor of i(logn factorization) */

namespace NT {

const int MAX_N = 1123456;

bitset<MAX_N> prime;
vector<int> primes;
int lf[MAX_N];
int totient[MAX_N];

void Sieve(int n) {
  for (int i = 0; i <= n; i++) lf[i] = i;
  prime.set();
  prime[0] = false;
  prime[1] = false;
  for (int p = 2; p * p <= n; p++) {
    if (prime[p]) {
      for (int i = p * p; i <= n; i += p) {
        prime[i] = false;
        lf[i] = min(lf[i], p);
      }
    }
  }
  for (int i = 2; i <= n; i++)
    if (prime[i]) primes.pb(i);
}

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
