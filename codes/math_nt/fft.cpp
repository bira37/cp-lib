/* Author: Ubiratan Correia Barbosa Neto
 */

/* Fast Fourier Transform Implementation */
/* Complex numbers implemented by hand */
/* Poly needs to have degree of next power of 2 (result poly has size
 * next_pot2(2*n) */
/* Uses Roots of Unity (Z^n = 1, divide and conquer strategy)
/* Inverse FFT only changes to the conjugate of Primitive Root of Unity */
/* Remember to use round to get integer value of Coefficients of Poly C */
/* Iterative FFT is way faster (bit reversal idea + straightforward conquer for
 * each block of each size) */
/* std::complex doubles the execution time */
/* FastConvolution receives a Poly A+Bi, and multiply A*B (imaginary part
 * doesn't remains the same)*/

namespace FFT {

struct Complex {
  double a, b;

  Complex(double a, double b) : a(a), b(b) {}

  Complex() : a(0), b(0) {}

  Complex conjugate() const { return Complex(a, -b); }

  double size2() const { return a * a + b * b; }

  void operator=(const Complex& b) {
    this->a = b.a;
    this->b = b.b;
  }
  void operator+=(const Complex& y) {
    this->a += y.a;
    this->b += y.b;
  }
  void operator-=(const Complex& y) {
    this->a -= y.a;
    this->b -= y.b;
  }
  void operator*=(const Complex& y) {
    *this = Complex(a * y.a - b * y.b, a * y.b + b * y.a);
  }
  Complex operator+(const Complex& y) const {
    return Complex(a + y.a, b + y.b);
  }
  Complex operator-(const Complex& y) const {
    return Complex(a - y.a, b - y.b);
  }
  Complex operator*(const Complex& y) const {
    return Complex(a * y.a - b * y.b, a * y.b + b * y.a);
  }
  Complex operator/(const double& x) const { return Complex(a / x, b / x); }
  Complex operator/(const Complex& y) const {
    return (*this) * (y.conjugate() / y.size2());
  }
};

struct Poly {
  vector<Complex> c;
  Poly() {}

  Poly(int n) {
    if (n <= 0) n = 1;
    c.resize(n);
  }

  Poly(const Poly& b) { copy(b); }

  void copy(const Poly& b) {
    c.clear();
    for (Complex elem : b.c) c.pb(elem);
  }

  void operator+=(const Poly& b) {
    while (size() < b.size()) c.pb(Complex(0, 0));
    for (int i = 0; i < b.size(); i++) c[i] += b.c[i];
  }

  void operator-=(const Poly& b) {
    while (size() < b.size()) c.pb(Complex(0, 0));
    for (int i = 0; i < b.size(); i++) c[i] -= b.c[i];
  }

  int size() const { return (int)c.size(); }

  Complex& operator[](int idx) {
    assert(idx < size());
    return c[idx];
  }
};

inline Complex PrimitiveRootOfUnity(int n) {
  const double PI = acos(-1);
  return Complex(cos(2 * PI / (double)n), sin(2 * PI / (double)n));
}

inline Complex InversePrimitiveRootOfUnity(int n) {
  const double PI = acos(-1);
  return Complex(cos(-2 * PI / (double)n), sin(-2 * PI / (double)n));
}

void DFT(Poly& A, bool inverse) {
  int n = A.size();
  int lg = 0;
  while (n > 0) lg++, n >>= 1;
  n = A.size();
  lg -= 2;

  for (int i = 0; i < n; i++) {
    int j = 0;
    for (int b = 0; b <= lg; b++) {
      if (i & (1 << b)) j |= (1 << (lg - b));
    }
    if (i < j) swap(A.c[i], A.c[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    Complex w;
    if (inverse)
      w = InversePrimitiveRootOfUnity(len);
    else
      w = PrimitiveRootOfUnity(len);

    for (int i = 0; i < n; i += len) {
      Complex x(1, 0);
      for (int j = 0; j < len / 2; j++) {
        Complex u = A.c[i + j], v = x * A.c[i + j + len / 2];
        A.c[i + j] = u + v;
        A.c[i + j + len / 2] = u - v;
        x *= w;
      }
    }
  }

  if (inverse)
    for (int i = 0; i < n; i++) A.c[i] = A.c[i] / n;
}

Poly FastMultiply(Poly& A, Poly& B) {
  Poly F_A(max(A.size(), B.size()));

  for (int i = 0; i < F_A.size(); i++) {
    F_A.c[i].a = (A.size() > i ? A.c[i].a : 0);
    F_A.c[i].b = (B.size() > i ? B.c[i].a : 0);
  }

  int n = 1;
  while (n < F_A.size() + F_A.size()) n <<= 1;
  F_A.c.resize(n);

  Poly C(F_A.size());

  DFT(F_A, false);

  for (int i = 0; i < F_A.size(); i++) F_A.c[i] *= F_A.c[i];

  DFT(F_A, true);

  for (int i = 0; i < F_A.size(); i++) C.c[i] = Complex(F_A.c[i].b / 2, 0);

  return C;
}

Poly Multiply(Poly& A, Poly& B) {
  Poly F_A(A), F_B(B);

  int n = 1;
  while (n < F_A.size() + F_B.size()) n <<= 1;
  F_A.c.resize(n);
  F_B.c.resize(n);

  DFT(F_A, false);

  DFT(F_B, false);

  for (int i = 0; i < F_A.size(); i++) F_A.c[i] *= F_B.c[i];

  DFT(F_A, true);

  return F_A;
}

Poly Double(Poly& A) {
  Poly F_A(A);

  int n = 1;
  while (n < F_A.size() + F_A.size()) n <<= 1;
  F_A.c.resize(n);

  DFT(F_A, false);

  for (int i = 0; i < F_A.size(); i++) F_A.c[i] *= F_A.c[i];

  DFT(F_A, true);

  return F_A;
}

};  // namespace FFT
