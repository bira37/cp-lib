/* Author: Ubiratan Correia Barbosa Neto
 * Erasthostenes Sieve Implementation + Euler's Totient
 */

/* Calculate primes from 2 to N */
/* lf[i] stores the lowest prime factor of i(logn factorization) */

namespace NT {

const int MAX_SIEVE = 1123456;

bitset<MAX_SIEVE> prime;
vector<int> primes;
vector<int> seg_primes;
int lf[MAX_SIEVE];
int totient[MAX_SIEVE];

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

void SegmentedSieve(int l, int r) {
  prime.set();
  seg_primes.clear();
  for (int p : primes) {
    int start = l - l % p - p;
    while (start < l) start += p;
    if (p == start) start += p;
    for (int i = start; i <= r; i += p) {
      prime[i - l] = false;
    }
  }
  for (int i = 0; i < r - l + 1; i++) {
    if (prime[i] && l + i > 1) {
      seg_primes.pb(l + i);
    }
  }
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
