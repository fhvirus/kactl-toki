/**
 * Author: FHVirus
 * Date: 2024-11-14
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: stress-tested & tested @ luogu P1742
 */
#pragma once

#include "Circumcircle.h"

template <class P>
vector<P> mec(vector<P> ps) {
  sort(all(ps)); ps.erase(unique(all(ps)), end(ps));
	shuffle(all(ps), mt19937(time(0)));
  vector<P> circ(1, ps[0]);
  const auto out = [&](P p) {
    if (sz(circ) == 1) return not (p == circ[0]);
    if (sz(circ) == 2)
      return sgn((p * 2 - (circ[0] + circ[1])).dist2()
        - (circ[0] - circ[1]).dist2()) > 0;
    return inCircumcircle(p, circ[0], circ[1], circ[2]) < 0;
  };
	rep(i,0,sz(ps)) if (out(ps[i])) {
    circ = {ps[i]};
		rep(j,0,i) if (out(ps[j])) {
      circ = {ps[i], ps[j]};
			rep(k,0,j) if (out(ps[k]))
        circ = {ps[i], ps[j], ps[k]};
		}
	}
	return circ;
}
