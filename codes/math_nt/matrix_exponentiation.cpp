/* Author: Ubiratan Correia Barbosa Neto
 * Matrix Exponentiation Implementation
 */

struct Matrix {
  vector<vector<int> > m;
  Matrix() {}
  Matrix(int l, int c) { m.resize(l, vector<int>(c)); }

  Matrix operator*(Matrix b) const {
    Matrix c(m.size(), b.m[0].size());
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < b.m[0].size(); j++) {
        for (int k = 0; k < b.m.size(); k++) {
          c.m[i][j] += (m[i][k] * b.m[k][j]);
          // c.m[i][j] = mod(c.m[i][j], M);
        }
      }
    }
    return c;
  }

  Matrix exp(int k) {
    if (k == 1) return *this;
    Matrix c = (*this).exp(k / 2);
    c = c * c;
    if (k % 2) c = c * (*this);
    return c;
  }
};
