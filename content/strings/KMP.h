/**
<<<<<<< HEAD
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
||||||| parent of fcedd4f (modify strings)
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
=======
 * Author: hhhhaura
 * Date: 2022/08/04
 * Description: $f[x]$ = the longest prefix $i$, so that $s(0:i)$ is a suffix of $s(0:x)$.
 * When $A_i \neq B_{j + 1}$ move $j$ to $f[j]$.
 * Time: $O(|A| + |B|)$
>>>>>>> fcedd4f (modify strings)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vi fail_function(string &s) {
	int n = sz(s);
	vi f(n, -1); // leave an additional space
	rep(i, 1, n - 1) {
		int cur = f[i - 1];
		while(cur != -1 && s[cur + 1] != s[i]) cur = f[cur];
		cur += (s[cur + 1] == s[i]);
		f[i] = cur;
	}
	return f;
}
int KMP(string &a, string &b) {
	vi f = fail_function(b);
	int j = -1, ans = 0;
	rep(i, 0, sz(a) - 1) {
		while(j != -1 && b[j + 1] != a[i]) j = f[j];
		j += (b[j + 1] == a[i]);
		ans += (j == sz(b));
	}
	return ans;
}
