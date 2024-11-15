/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Source: ckiseki
 * Description: Given weight matrix, find maximum perfect matching.
 * Time: $O(N^3)$
 * Status: tested @ uoj:80
 */
#pragma once

const ll INF = numeric_limits<ll>::max() / 4;
struct KM {
  int n, l, r; ll ans; // fl and fr are the match
  vector<ll> hl, hr; vector<int> fl, fr, pre, q;
  void bfs(const vector<vector<ll>> &w, int s) {
    vector<int> vl(n), vr(n); vector<ll> slk(n, INF);
    l = r = 0; vr[q[r++] = s] = true;
    auto check = [&](int x) -> bool {
      if (vl[x] || slk[x] > 0) return true;
      vl[x] = true; slk[x] = INF;
      if (fl[x] != -1) return (vr[q[r++] = fl[x]] = true);
      while (x != -1) swap(x, fr[fl[x] = pre[x]]);
      return false;
    };
    while (true) {
      while (l < r)
        for (int x = 0, y = q[l++]; x < n; ++x) if (!vl[x])
          if (slk[x] > hl[x] + hr[y] - w[x][y]) {
            slk[x] = hl[x] + hr[y] - w[x][y];
            if (pre[x] = y, !check(x)) return;
          }
      ll d = *min_element(all(slk));
      for (int x = 0; x < n; ++x)
        vl[x] ? hl[x] += d : slk[x] -= d;
      for (int x = 0; x < n; ++x) if (vr[x]) hr[x] -= d;
      for (int x = 0; x < n; ++x) if (!check(x)) return;
    }
  }
  KM(int n_, const vector<vector<ll>> &w) : n(n_), ans(0),
    hl(n), hr(n), fl(n, -1), fr(fl), pre(n), q(n) {
    for (int i = 0; i < n; ++i) hl[i]=*max_element(all(w[i]));
    for (int i = 0; i < n; ++i) bfs(w, i);
    for (int i = 0; i < n; ++i) ans += w[i][fl[i]];
  }
};
