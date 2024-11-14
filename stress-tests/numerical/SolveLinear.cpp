#include "../utilities/template.h"

const int mod = 3;
const int nmax = 4, mmax = 4, nmmax = 10;

const int lut[9] = {-4,-2,-3,-1,-100,1,3,2,4};

int modinv(int x) {
	assert(x);
	return x;
	// return lut[x+4];
}

const double eps = 1e-12;
template <class T>
struct LinearSolver {
  typedef vector<T> vt;
  vector<vt> A, B;
  vt b, x;
  int rank;
  LinearSolver(const vector<vt>& _A, const vt& _b) :
    A(_A), b(_b), rank(0) {
    if (A.empty()) return;
    int n = sz(A), m = sz(A[0]), br, bc;
    vi col(m); iota(all(col), 0);

    rep (i, 0, n) {
      T v, bv = T(0);
      rep (r, i, n) rep(c, i, m)
        if ((v = A[r][c]) != 0) // mod: v != 0
          br = r, bc = c, bv = v;
      if (bv == 0) { // mod: bv == 0 / b[j] != 0
        rep (j, i, n) if (b[j] != 0) {
          rank = -1; return; }
        break;
      }
      swap(A[i], A[br]);
      swap(b[i], b[br]);
      swap(col[i], col[bc]);
      rep (j, 0, n) swap(A[j][i], A[j][bc]);
      rep (j, i+1, m) A[i][j] = A[i][j] * modinv(A[i][i]) % mod;
      b[i] = b[i] * modinv(A[i][i]) % mod;
      A[i][i] = T(1);
      rep (j, 0, n) if (j != i) {
        T fac = A[j][i];
        b[j] = (b[j] - fac * b[i] % mod + mod) % mod;
        rep (k, i, m) A[j][k] = (A[j][k] - fac * A[i][k] % mod + mod) % mod;
      }
      rank++;
    }
    x.assign(m, T(0));
    for (int i = rank; i--;) {
      x[col[i]] = b[i];
      rep (j, 0, i) b[j] = (b[j] - A[j][i] * b[i] % mod + mod) % mod;
    }
    rep (i, rank, m) { // homo sols
      vt sol(m, T(0)); sol[col[i]] = T(1);
      rep (j, 0, rank) sol[col[j]] = (A[j][i] * T(mod-1) % mod);
      B.push_back(sol);
    }
  }
};

typedef vector<int> vd;

template<class F>
void rec(int i, int j, vector<vd>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		rep(v,0,mod) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vd& A, F f) {
	if (i == sz(A)) f();
	else {
		rep(v,0,mod) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	rep(n,0,nmax+1) rep(m,0,mmax+1) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<vd> A(n, vd(m));
		vd b(n), x(m), theX(m);
		rec(0, 0, A, [&]() {
			rec2(0, b, [&]() {
				int sols = 0;
				rec2(0, x, [&]() {
					rep(i,0,n) {
						int v = 0;
						rep(j,0,m) v += A[i][j] * x[j];
						if (v % mod != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
        LinearSolver<int> solver(A, b);
        int r = solver.rank;
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(solver.x == theX);
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
