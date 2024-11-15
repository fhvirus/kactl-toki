/**
 * Author: Jikuai
 * Date: 2024-11-15
 * License: CC0
 * Description: Add segment
 * Time: O(N + Q \log N).
 * Status: not tested
 */
#pragma once
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
struct line {
  ll a, b;
  ll operator()(const ll x) const {
    return a * x + b;
  }
};
struct lichao {
  size_t size;
  vector<ll> xs;
  vector<size_t> left, right;
  vector<line> best;
  explicit lichao(const vector<ll>& xs_) : xs(xs_) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    const size_t n = xs.size();
    size = 1;
    while (size < n) size <<= 1;
    xs.resize(size, xs.back());
    left.resize(2 * size);
    right.resize(2 * size);
    best.resize(2 * size, {0, LINF});
    for (size_t i = 0; i < size; ++i)
      left[i + size] = right[i + size] = i;
    for (size_t i = size - 1; i > 0; --i) {
      left[i] = left[i << 1];
      right[i] = right[i << 1 | 1];
    }
  }
  inline size_t get_id(ll p) const {
    return lower_bound(all(xs), p) - begin(xs) + size;
  }
  void add_segment(const ll l, const ll r, const line& add) {
    size_t a = get_id(l), b = get_id(r);
    while (a < b) {
      if (a & 1) add_line(a++, add);
      if (b & 1) add_line(--b, add);
      a >>= 1, b >>= 1;
    }
  }
  ll que(const ll x) {
    size_t k = get_id(x);
    ll ret = LINF;
    while (k > 0) {
      ret = min(ret, best[k](x));
      k >>= 1;
    }
    return ret;
  }
  void add_line(size_t k, line add) {
    const size_t l = left[k];
    const size_t r = right[k];
    const size_t m = (l + r) / 2;
    auto& cur = best[k];
    if (add(xs[m]) < cur(xs[m])) swap(add, cur);
    if (add(xs[l]) < cur(xs[l])) add_line(k << 1, add);
    if (add(xs[r]) < cur(xs[r])) add_line(k << 1 | 1, add);
  }
};
