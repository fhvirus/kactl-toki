/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Description: p[x] = max j s.t. j <= i and s[0, j-1] = s[i-j+1, i], p[0] = 0
 * Time: $O(|P| + |T|)$
 * Status: Tested on tioj:1306
 * License: CC0
 */
#pragma once

vi fail_function(const string &s) { // begin-hash
  vi p(sz(s));
  rep (i, 1, sz(s)) {
    int j = p[i - 1];
    while (j > 0 and s[j] != s[i]) j = p[j-1];
    p[i] = j + (s[i] == s[j]);
  }
  return p;
} // end-hash
int match(const string &T, const string &P) {
  auto a = fail_function(P + '$');
  int ans = 0, j = 0;
  rep (i, 0, sz(T)) {
    while (j > 0 and T[i] != P[j]) j = a[j-1];
    j += (T[i] == P[j]);
    ans += (j == sz(P));
  }
  return ans;
}
