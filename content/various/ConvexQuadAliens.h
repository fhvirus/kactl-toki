/**
 * Author: FHVirus
 * License: CC0
 * Source: TIOJ 1986
 * Description:
 * Time: $O(N \log N \log (rb - lb))$
 */

vector<pair<ll, int>> dp(N + 1); // (min cost, cnt)
deque<pii> dq; // (source, best until)
const auto quad_aliens = [&](int n, int k) -> ll {
  const auto f = [&](int j, int i, ll pen) -> pair<ll, int> {
    return { dp[j].first + cost(j, i) + pen,
      dp[j].second + 1 }; };
  const auto find_t = [&](int u, int v, int lb, int rb) {
    rb += 1;
    while (lb < rb) {
      int mid = (lb + rb) / 2;
      if (f(u, mid, 0) <= f(v, mid, 0)) lb = mid + 1;
      else rb = mid;
    }
    return lb;
  };
  const auto solve = [&](const ll pen) -> void {
    dp[0] = pair<ll, int>(0, 0);
    dq.clear(); dq.emplace_back(0, n);
    rep (i, 1, n + 1) {
      while (dq.front().second < i) dq.pop_front();
      dp[i] = f(dq.front().first, i, pen);
      int mid = -1;
      while (!dq.empty()) {
        int lb = (sz(dq) == 1 ? dq.back().first : end(dq)[-2].second + 1);
        if (f(dq.back().first, lb, 0) >= f(i, lb, 0)) {
          dq.pop_back(); continue; }
        mid = find_t(dq.back().first, i, lb, dq.back().second);
        if (mid <= lb) dq.pop_back(); else break;
      }
      if (!dq.empty() && mid <= n) {
        dq.back().second = mid - 1;
        dq.emplace_back(i, n);
      } else if (dq.empty())
        dq.emplace_back(i, n);
    }
  };
  // beware fp precision / range
  ll lb = 0, rb = 1e11;
  while (lb < rb) {
    ll mid = (lb + rb) / 2;
    solve(mid);
    if (dp[n].second > k) lb = mid + 1;
    else rb = mid;
  }
  solve(lb);
  return dp[n].first - lb * k;
};
