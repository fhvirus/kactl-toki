/**
 * Author: FHVirus
 * Date: 2024-11-14
 * License: CC0
 * Description: Solves $A * (x + B^T y) = b$, where $y$ is an arbitrary vector.
 *  If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. B are the m - rank solutions for Ax = 0.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolverplus, librarychecker:system_of_linear_equations,
 *  and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once
const double eps = 1e-12;
template <class T>
struct LinearSolver {
  typedef vector<T> vt;
  vector<vt> A, B;
  vt b, x;
  int rank;
  LinearSolver(const vector<vt>& _A, const vt& _b) :
    A(_A), b(_b), rank(0) {
    int n = sz(A), m = sz(A[0]), br, bc;
    vi col(m); iota(all(col), 0);

    rep (i, 0, n) {
      T v, bv = T(0);
      rep (r, i, n) rep(c, i, m)
        if ((v = fabs(A[r][c])) > bv) // mod: v != 0
          br = r, bc = c, bv = v;
      if (bv <= eps) { // mod: bv == 0 / b[j] != 0
        rep (j, i, n) if (fabs(b[j]) > eps) {
          rank = -1; return; }
        break;
      }
      swap(A[i], A[br]);
      swap(b[i], b[br]);
      swap(col[i], col[bc]);
      rep (j, 0, n) swap(A[j][i], A[j][bc]);
      rep (j, i+1, m) A[i][j] /= A[i][i];
      b[i] /= A[i][i];
      A[i][i] = T(1);
      rep (j, 0, n) if (j != i) {
        T fac = A[j][i];
        b[j] -= fac * b[i];
        rep (k, i, m) A[j][k] -= fac * A[i][k];
      }
      rank++;
    }
    x.assign(m, T(0));
    for (int i = rank; i--;) {
      x[col[i]] = b[i];
      rep (j, 0, i) b[j] -= A[j][i] * b[i];
    }
    rep (i, rank, m) { // homo sols
      vt sol(m, T(0)); sol[col[i]] = T(1);
      rep (j, 0, rank) sol[col[j]] = (A[j][i] * T(-1));
      B.push_back(sol);
    }
  }
};
