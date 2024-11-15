/**
 * Author: FHVirus
 * Source: 8BQube
 * Date: 2024-11-15
 * Description: 
 * Usage: Number of different substrings (sum len[i] - len[link[i]])
 * 	Number of occurrences of string P (sum cnt[i])
 * 	Shortest non-appearing string (d[u] = 1 + min d[v]).
 * 	LCS (substring) of multiple strings.
 * Time: $O(\sum |S|)$
 * Status: Tested @ luogu:P6139
 */
struct SuffixAutomaton {
  enum { sigma = 26, first = 'a' };
  struct Node {
    int len, link, next[sigma]; ll cnt;
    Node(int v) : len(0), link(0), cnt(0)
    { memset(next, v, sizeof(next)); }
  };
  vector<Node> nd;
  vi ord;
  SuffixAutomaton() : nd(1, -1) { nd[0].link = -1; }
  int insert(const string &s) {
    assert(!s.empty());
    int u = 0;
    for (char c : s) {
      int &v = nd[u].next[c - first];
      if (v == -1) { u = v = sz(nd); nd.emplace_back(-1); }
      else u = v;
      nd[u].cnt += 1;
    }
    return u;
  }
  int extend(int u, int c) {
    int v = nd[u].next[c];
    nd[v].len = nd[u].len + 1;
    int p = nd[u].link;
    while (p != -1 && nd[p].next[c] == -1)
      nd[p].next[c] = v, p = nd[p].link;
    if (p == -1) return nd[v].link = 0, v;
    int y = nd[p].next[c];
    if (nd[p].len + 1 == nd[y].len) return nd[v].link = y, v;
    int clone = sz(nd); nd.emplace_back(-1);
    rep (i, 0, sigma) nd[clone].next[i] =
      (nd[nd[y].next[i]].len > 0 ? nd[y].next[i] : 0);
    nd[clone].len = nd[p].len + 1;
    while (p != -1 && nd[p].next[c] == y)
      nd[p].next[c] = clone, p = nd[p].link;
    nd[nd[v].link = clone].link = nd[y].link;
    nd[y].link = clone;
    return v;
  }
  void build() {
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int u = q.front();
      rep (c, 0, sigma) if (nd[u].next[c] != -1)
        q.push(extend(u, c));
    }
    vi cnt(sz(nd)); ord.resize(sz(nd) - 1);
    rep (i, 1, sz(nd)) ++cnt[nd[i].len];
    partial_sum(all(cnt), begin(cnt));
    rep (i, 1, sz(nd)) ord[--cnt[nd[i].len]] = i;
    for (int i = sz(ord) - 1; i >= 0; --i)
      nd[nd[ord[i]].link].cnt += nd[ord[i]].cnt;
  }
};
