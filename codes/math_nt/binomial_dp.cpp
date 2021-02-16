/* Author: Ubiratan Correia Barbosa Neto
 * Binomial Coefficient
 */

/* Dynammic Programming for Binomial Coefficient Calculation */
/* Using Stiefel Rule C(n, k) = C(n-1, k) + C(n-1, k-1) */

int binomial(int n, int k) {
  int c[n + 10][k + 10];
  memset(c, 0, sizeof c);
  c[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = min(i, k); j > 0; j--) {
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
  }
  return c[n][k];
}
