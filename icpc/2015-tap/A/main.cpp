#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for(int i = 0; i < n; ++i)
#define fore(i, z, n) for(int i = z; i < n; ++i)

typedef long double ld;
ld EPS = 1e-9;

struct pt {
	ld x, y;
	pt(ld x, ld y):x(x),y(y){}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	pt operator+(pt p){return pt(x+p.x, y+p.y);}
	pt operator-(pt p){return pt(x-p.x, y-p.y);}
	pt operator/(ld t){return pt(x/t, y/t);}
	pt operator*(ld t){return pt(x*t, y*t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
	ld operator%(pt p){return x*p.y-y*p.x;}

	pt rot(pt r){return pt(*this%r, *this*r);}
};

pt ccw90(1, 0);
pt cw90(-1, 0);

struct circle {
	pt o; ld r;
	circle(){}
	circle(pt o, ld r): o(o), r(r) {}
	void inter(circle c, pt &a, pt &b) {
		a = o;
		b = o;
		vector<pt> s;
		ld d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return;
		ld x =(d*d-c.r*c.r+r*r)/(2*d);
		ld y = sqrt(r*r-x*x);
		pt v = (c.o-o)/d;

		a = o+v*x-v.rot(ccw90)*y;
		b = o+v*x+v.rot(ccw90)*y;
	}
	bool has(pt p){return (o-p).norm()<=r+EPS;}
};

int main() {
	int n;
	ios::sync_with_stdio(false);
	cin.tie(0);
	while(cin >> n) {
		vector<circle> ns(n);
		forn(i, n) cin >> ns[i].o.x >> ns[i].o.y >> ns[i].r;

		int best = 0;
		forn(i, n) forn(j, i) {
			pt a, b;
			ns[i].inter(ns[j], a, b);
			int tota = 0;
			int totb = 0;
			forn(k, n) {
				if(ns[k].has(a)) tota++;
				if(ns[k].has(b)) totb++;
			}
			best = max(best, tota);
			best = max(best, totb);
		}
		cout << best << "\n";
	}
}
