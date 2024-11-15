/**
 * Author: FHVirus
 * Date: 2024-11-15
 * Source: Original kactl
 * Description: Aho-Corasick automaton.
 * To find all words, build a linked tree of patterns.
 * To find the longest words that start at each position, reverse all input.
 * Be careful of the extra node.
 * Time: $O(\sigma N)$ construction, where $N =$ sum of length of patterns.
 * Status: Tested @ tioj:1306
 */
#pragma once

struct AhoCorasick {
	enum { sigma = 26, first = 'a' }; // change this!
	struct Node {
		int fl, next[sigma];
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> nd;
	vi ord;
	AhoCorasick() : nd(1, -1) {}
	int insert(const string& s) {
		assert(!s.empty());
		int u = 0;
		for (char c : s) {
			int &v = nd[u].next[c - first];
			if (v == -1) { u = v = sz(nd); nd.emplace_back(-1); }
			else u = v;
		}
    return u;
	}
  void build() {
		nd[0].fl = sz(nd);
		nd.emplace_back(0);
    ord.push_back(0);
    rep (i, 0, sz(ord)) {
			int u = ord[i], pre = nd[u].fl;
			rep (c, 0, sigma) {
				int &v = nd[u].next[c], y = nd[pre].next[c];
				if (v == -1) v = y;
				else nd[v].fl = y, ord.push_back(v);
			}
		}
	}
};
