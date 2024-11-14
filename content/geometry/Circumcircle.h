/**
 * Author: Ulf Lundstrom, FHVirus
 * Date: 2024-11-14
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices.
ccRadius returns the radius of the circle going through
points A, B and C and ccCenter returns the center of the same circle.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/Circumcircle}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

template <class P> // in/on/out: >/=/< 0 begin-hash
int inCircumcircle(P o, P a, P b, P c) {
  a = a - o, b = b - o, c = c - o;
  if (a.cross(b, c) < 0) swap(b, c);
  __int128 za = a.dist2(), zb = b.dist2(), zc = c.dist2();
  __int128 t = za * b.cross(c) -
    zb * a.cross(c) + zc * a.cross(b); // C^4
  return sgn(t);
} // end-hash

template <class P>
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
template <class P>
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}
