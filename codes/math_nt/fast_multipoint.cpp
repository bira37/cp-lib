/* I am not the author of this code. This code was taken from the original source and updated to fit my code style. Author comment below
 * Source: from https://github.com/ecnerwala/icpc-book/blob/master/content/numerical/fft.cpp 
 */

/**
 * Author: Andrew He
 * Description: FFT/NTT, polynomial mod/log/exp
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Papers about accuracy: http://www.daemonology.net/papers/fft.pdf, http://www.cs.berkeley.edu/~fateman/papers/fftvsothers.pdf
 * For integers rounding works if $(|a| + |b|)\max(a, b) < \mathtt{\sim} 10^9$, or in theory maybe $10^6$.
 */

namespace FastInterpolation {
const int mod = 998244353, g = 3;
struct num {
  int v;
  num(ll v_ = 0) : v((int)(v_ % mod)) {
    if (v < 0) v += mod;
  }
  explicit operator int() const { return v; }
};

inline num operator+(num a, num b) { return num(a.v + b.v); }
inline num operator-(num a, num b) { return num(a.v + mod - b.v); }
inline num operator*(num a, num b) { return num(1ll * a.v * b.v); }
inline num pow(num a, int b) {
  num r = 1;
  do {
    if (b & 1) r = r * a;
    a = a * a;
  } while (b >>= 1);
  return r;
}
inline num inv(num a) { return pow(a, mod - 2); }

using vn = vector<num>;
vector<int> rev({0, 1});
vn rt(2, num(1)), fa, fb;
using poly = vn;
inline int sz(const poly& p) { return p.size(); }

inline void init(int n) {
  if (n <= sz(rt)) return;
  rev.resize(n);
  for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | ((i & 1) * n)) >> 1;
  rt.reserve(n);
  for (int k = sz(rt); k < n; k *= 2) {
    rt.resize(2 * k);
    num z = pow(num(g), (mod - 1) / (2 * k));
    for (int i = k / 2; i < k; i++)
      rt[2 * i] = rt[i], rt[2 * i + 1] = rt[i] * z;
  }
}

inline void fft(vector<num>& a, int n) {
  init(n);
  int s = __builtin_ctz(rev.size() / n);
  for (int i = 0; i < n; i++)
    if (i < (rev[i] >> s)) swap(a[i], a[rev[i] >> s]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        num t = rt[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - t;
        a[i + j] = a[i + j] + t;
      }
}

vn multiply(vn a, vn b) {
  int s = sz(a) + sz(b) - 1;
  if (s <= 0) return {};
  int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
  a.resize(n), b.resize(n);
  fft(a, n);
  fft(b, n);
  num d = inv(num(n));
  for (int i = 0; i < n; i++) a[i] = a[i] * b[i] * d;
  reverse(a.begin() + 1, a.end());
  fft(a, n);
  a.resize(s);
  return a;
}

vn inverse(const vn& a) {
  if (a.empty()) return {};
  vn b({inv(a[0])});
  b.reserve(2 * a.size());
  while (sz(b) < sz(a)) {
    int n = 2 * sz(b);
    b.resize(2 * n, 0);
    if (sz(fa) < 2 * n) fa.resize(2 * n);
    fill(fa.begin(), fa.begin() + 2 * n, 0);
    copy(a.begin(), a.begin() + min(n, sz(a)), fa.begin());
    fft(b, 2 * n);
    fft(fa, 2 * n);
    num d = inv(num(2 * n));
    for (int i = 0; i < 2 * n; i++) b[i] = b[i] * (2 - fa[i] * b[i]) * d;
    reverse(b.begin() + 1, b.end());
    fft(b, 2 * n);
    b.resize(n);
  }
  b.resize(a.size());
  return b;
}

poly& operator+=(poly& a, const poly& b) {
  if (sz(a) < sz(b)) a.resize(b.size());
  for (int i = 0; i < sz(b); i++) a[i] = a[i] + b[i];
  return a;
}
poly operator+(const poly& a, const poly& b) {
  poly r = a;
  r += b;
  return r;
}
poly& operator-=(poly& a, const poly& b) {
  if (sz(a) < sz(b)) a.resize(b.size());
  for (int i = 0; i < sz(b); i++) a[i] = a[i] - b[i];
  return a;
}
poly operator-(const poly& a, const poly& b) {
  poly r = a;
  r -= b;
  return r;
}

poly operator*(const poly& a, const poly& b) { return multiply(a, b); }

poly operator/(poly a, poly b) {
  if (sz(a) < sz(b)) return {};
  int s = sz(a) - sz(b) + 1;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  a.resize(s);
  b.resize(s);
  a = a * inverse(move(b));
  a.resize(s);
  reverse(a.begin(), a.end());
  return a;
}
poly& operator/=(poly& a, const poly& b) { return a = a / b; }

poly& operator%=(poly& a, const poly& b) {
  if (sz(a) >= sz(b)) {
    poly c = (a / b) * b;
    a.resize(sz(b) - 1);
    for (int i = 0; i < sz(a); i++) a[i] = a[i] - c[i];
  }
  return a;
}

poly operator%(const poly& a, const poly& b) {
  poly r = a;
  r %= b;
  return r;
}

poly deriv(const poly& a) {
  if (a.empty()) return {};
  poly b(sz(a) - 1);
  for (int i = 0; i < sz(a); i++) b[i - 1] = a[i] * i;
  return b;
}

vector<num> PolyMultiEvaluation(const poly& a, const vector<num>& x) {
  int n = sz(x);
  if (!n) return {};
  vector<poly> up(2 * n);
  for (int i = 0; i < n; i++) up[i + n] = poly({0 - x[i], 1});
  for (int i = n - 1; i >= 1; i--) up[i] = up[2 * i] * up[2 * i + 1];
  vector<poly> down(2 * n);
  down[1] = a % up[1];
  for (int i = 2; i < 2 * n; i++) down[i] = down[i / 2] % up[i];
  vector<num> y(n);
  for (int i = 0; i < n; i++) y[i] = down[i + n][0];
  return y;
}

vector<num> PolyMultiInterpolation(const vector<num>& x, const vector<num>& y) {
  int n = sz(x);
  assert(n);
  vector<poly> up(n * 2);
  for (int i = 0; i < n; i++) up[i + n] = poly({0 - x[i], 1});
  for (int i = n - 1; i >= 1; i--) up[i] = up[2 * i] * up[2 * i + 1];
  vector<num> a = PolyMultiEvaluation(deriv(up[1]), x);
  vector<poly> down(2 * n);
  for (int i = 0; i < n; i++) down[i + n] = poly({y[i] * inv(a[i])});
  for (int i = n - 1; i >= 1; i--)
    down[i] = down[i * 2] * up[i * 2 + 1] + down[i * 2 + 1] * up[i * 2];
  return down[1];
}
}  // namespace FastInterpolation
