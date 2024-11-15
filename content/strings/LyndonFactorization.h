/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Description: Partition $S = w[0] + w[1] + ...$ s.t.
 *  w[0] >= w[1] >= ... and w[i] is < than all its cyclic shifts
 * Time: $O(|S|)$
 * Status: not tested
 */
#pragma once

vector<pii> duval(const string& s) {
  vector<pii> res;
  for (int n = sz(s), i = 0, j, k; i < n; ) {
    for (j = i + 1, k = i; j < n && s[k] <= s[j]; ++j)
      k = (s[k] < s[j] ? i : k + 1);
    for (; i <= k; i += j - k) res.emplace_back(i, j - k);
  }
}
