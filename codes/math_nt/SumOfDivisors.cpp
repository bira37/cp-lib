/* Author: Ubiratan Correia Barbosa Neto
 * Sum of Divisors
 */

namespace NT {

int SumOfDivisors(int a, int b) {
  int m = sqrt(b);
  int s = 0;
  for (int f = 1; f <= m; f++) {
    int x = (b / f) * (b / f) - max(m, (a - 1) / f) * max(m, (a - 1) / f) +
            (b / f) - max(m, (a - 1) / f);
    s += f * (b / f - (a - 1) / f);
    s += x / 2;
  }
  return s;
}

}  // namespace NT
