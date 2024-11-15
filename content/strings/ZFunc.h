/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Description: z[i] = max j s.t. s[0, j) = s[i, i+j), z[0] = 0
 * Time: $O(|P| + |T|)$
 * Status: Tested @ tioj:1306
 * License: CC0
 */
#pragma once

vi z_func(const string &s) { // begin-hash
  vi z(sz(s));
  int l = 0, r = 0;
  rep (i, 1, sz(s)) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < sz(s) and s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
} // end-hash
int match(const string &T, const string &P) {
  auto z = z_func(P + '$' + T);
  int ans = 0;
  rep (i, 0, sz(T))
    ans += (z[sz(P) + 1 + i] == sz(P));
  return ans;
}
