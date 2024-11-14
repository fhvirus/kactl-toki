/**
 * Author: FHVirus
 * Date: 2024-11-14
 * License: CC0
 * Source: ckiseki's codebook
 * Description: Calculate $\det(xI - M)$.
 * Time: O(N^3)
 * Status: Tested @ yosupo:characteristic_polynomial
 */
#pragma once

#include "../number-theory/ModPow.h"

const ll mod = 998244353;
template <class T>
void Hessenberg(int n, vector<vector<T>> &a) {
  rep (i, 0, n - 2) {
    rep (j, i + 1, n) if (a[j][i]) {
      rep (k, i, n) swap(a[i+1][k], a[j][k]);
      rep (k, 0, n) swap(a[k][i+1], a[k][j]);
      break;
    }
    if (a[i + 1][i] == 0) continue;
    rep (j, i + 2, n) {
      T c = modpow(a[i + 1][i], mod-2, mod) * a[j][i] % mod;
      rep (k, i, n)
        a[j][k] = (a[j][k] - a[i+1][k] * c % mod + mod) % mod;
      rep (k, 0, n) a[k][i+1] = (a[k][i+1] + a[k][j] * c) % mod;
    }
  }
}
template <class T>
vector<T> CharPoly(vector<vector<T>> a) {
  int n = sz(a); Hessenberg(n, a);
  vector<vector<T>> p(n + 1, vector<T>(n + 1)); p[0][0] = 1;
  rep (i, 1, n + 1) {
    rep (j, 0, i + 1) p[i][j] = j ? p[i - 1][j - 1] : 0;
    T val = 1;
    for (int j = i - 1; j >= 0; --j) {
      T c = val * a[j][i - 1] % mod;
      rep (k, 0, j + 1)
        p[i][k] = (p[i][k] - p[j][k] * c % mod + mod) % mod;
      if (j) val = val * a[j][j - 1] % mod;
    }
  }
  return p[n];
}
