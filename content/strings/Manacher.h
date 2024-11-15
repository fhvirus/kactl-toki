/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Description: Computes the longest palindromic subsequence in string. even indices are padded with char '.'.
 * Time: O(N)
 * Status: Tested @ yosupo:enumerate_palindromes
 * Usage: $p_i - 1 = $ length centered at i
 */
#pragma once

vi Manacher(string s) {
  string t(sz(s) * 2 + 1, '.');
  rep (i, 0, sz(s)) t[i * 2 + 1] = s[i];
  int n = sz(t), m = 0, r = 0;
  vi p(n);
  rep (i, 0, n) {
    p[i] = (r > i ? min(r - i, p[m - (i - m)]) : 1);
    while (0 <= i - p[i] and i + p[i] < n and
        t[i - p[i]] == t[i + p[i]]) ++p[i];
    if (i + p[i] > r) m = i, r = i + p[i];
  }
  return p;
}
