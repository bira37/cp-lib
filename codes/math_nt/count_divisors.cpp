/* Author: Ubiratan Correia Barbosa Neto
 * Count Divisors
 */

namespace NT {

int CountDivisors(int x) {
  int ans = 1;
  for (int i = 2; i * i * i <= x; i++) {
    int cnt = 1;
    while (x % i == 0) {
      cnt++;
      x /= i;
    }
    ans *= cnt;
  }

  if (PrimalityTest(x, 15))
    ans *= 2;
  else if ((int)sqrt(x) * (int)sqrt(x) == x && PrimalityTest((int)sqrt(x), 15))
    ans *= 3;
  else if (x != 1)
    ans *= 4;

  return ans;
}

}  // namespace NT
