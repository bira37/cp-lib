/* Author: Ubiratan Correia Barbosa Neto
 * Miller Rabin
 */

namespace NT {

int mulmod(int a, int b, int c) {
  int x = 0, y = a % c;

  while (b > 0) {
    if (b % 2 == 1) {
      x = (x + y) % c;
    }

    y = (y * 2) % c;
    b /= 2;
  }

  return x % c;
}

int expmod(int a, int k, int p) {
  if (k == 0) return 1;
  if (k == 1) return a;

  int aux = expmod(a, k / 2, p);
  aux = mulmod(aux, aux, p);

  if (k % 2) aux = mulmod(aux, a, p);
  return aux;
}

bool PrimalityTest(int p, int iterations) {
  // Miller Rabin Primality Test
  mt19937 mt_rand(time(0));

  if (p < 2) return false;
  if (p == 2) return true;
  if (p % 2 == 0) return false;

  int fixed_s = p - 1;
  while (fixed_s % 2 == 0) fixed_s /= 2;

  for (int iter = 0; iter < iterations; iter++) {
    int s = fixed_s;

    int a = mt_rand() % (p - 1) + 1;
    int b = expmod(a, s, p);

    while (s != p - 1 && b != 1 && b != p - 1) {
      b = mulmod(b, b, p);
      s *= 2;
    }

    if (b != p - 1 && s % 2 == 0) return false;
  }

  return true;
}

}  // namespace NT
