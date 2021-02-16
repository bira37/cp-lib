/**
 * I'm not the author. Just adding for simple copy-paste
 * Source:  kth-competitive-programming / kactl
 * Link:
 * https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/Simplex.h
 * Simplex slightly modified
 */
namespace LinearProgramming {
/**
 * Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize $c^T x$
 * subject to $Ax \le b$, $x \ge 0$. Returns -inf if there is no solution, inf
 * if there are arbitrarily good solutions, or the maximum value of $c^T x$
 * otherwise. The input vector is set to an optimal $x$ (or in the unbounded
 * case, an arbitrary solution fulfilling the constraints). Numerical stability
 * is not guaranteed. For better performance, define variables such that $x = 0$
 * is viable. Usage: vvd A = {{1,-1}, {-1,1}, {-1,-2}}; vd b = {1,1,-4}, c =
 * {-1,-1}, x; T val = LPSolver(A, b, c).solve(x); Time: O(NM * \#pivots), where
 * a pivot may be e.g. an edge relaxation. O(2^n) in the general case. Status:
 * seems to work?
 */

typedef double T;        // long double, Rational, double + mod<P>...
typedef vector<T> vd;    // Vector
typedef vector<vd> vvd;  // Matrix

const T eps = 1e-8, inf = 1 / .0;
#define lpsolver_ltj(X) \
  if (s == -1 || mp(X[j], N[j]) < mp(X[s], N[s])) s = j

struct LPSolver {
  int m, n;
  vi N, B;
  vvd D;

  int sz(const vd& v) { return (int)(v.size()); }

  LPSolver(const vvd& A, const vd& b, const vd& c)
      : m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
    rep(i, 0, m, 1) rep(j, 0, n, 1) D[i][j] = A[i][j];
    rep(i, 0, m, 1) {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n + 1] = b[i];
    }
    rep(j, 0, n, 1) {
      N[j] = j;
      D[m][j] = -c[j];
    }
    N[n] = -1;
    D[m + 1][n] = 1;
  }

  void pivot(int r, int s) {
    T *a = D[r].data(), inv = 1 / a[s];
    rep(i, 0, m + 2, 1) if (i != r && abs(D[i][s]) > eps) {
      T *b = D[i].data(), inv2 = b[s] * inv;
      rep(j, 0, n + 2, 1) b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }
    rep(j, 0, n + 2, 1) if (j != s) D[r][j] *= inv;
    rep(i, 0, m + 2, 1) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = -1;
      rep(j, 0, n + 1, 1) if (N[j] != -phase) lpsolver_ltj(D[x]);
      if (D[x][s] >= -eps) return true;
      int r = -1;
      rep(i, 0, m, 1) {
        if (D[i][s] <= eps) continue;
        if (r == -1 ||
            mp(D[i][n + 1] / D[i][s], B[i]) < mp(D[r][n + 1] / D[r][s], B[r]))
          r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }

  T solve(vd& x) {
    int r = 0;
    rep(i, 1, m, 1) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
      rep(i, 0, m, 1) if (B[i] == -1) {
        int s = 0;
        rep(j, 1, n + 1, 1) lpsolver_ltj(D[i]);
        pivot(i, s);
      }
    }
    bool ok = simplex(1);
    x = vd(n);
    rep(i, 0, m, 1) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};

}  // namespace LinearProgramming
