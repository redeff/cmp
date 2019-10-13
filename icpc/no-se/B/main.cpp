#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld EPS = 1e-14;

struct pt {
	ld x,y;
	pt(ld x, ld y): x(x), y(y) {}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x) < EPS && abs(y-p.y) < EPS;}
	pt operator+(pt p){return pt(x+p.x, y+p.y);}
	pt operator-(pt p){return pt(x-p.x, y-p.y);}
	pt operator*(ld t){return pt(x*t, y*t);}
	pt operator/(ld t){return pt(x/t, y/t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
	ld operator%(pt p){return x*p.y-y*p.x;}
	pt rot(pt r){return pt(*this%r, *this*r);}
	pt unit() {return *this/norm();}
};

pt ccw90(1, 0);
pt nop(98127.0, 128347.4341);

struct circle {
	pt o; ld r;
	circle(){}
	circle(pt o, ld r): o(o), r(r) {}

	vector<pt> operator^(circle c) {
		vector<pt> s;
		ld d = (o-c.o).norm();
		assert(d<r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r));
		ld x = (d*d-c.r*c.r+r*r)/(2*d);
		ld y = sqrt(r*r-x*x);
		pt v = (c.o-o)/d;
		s.push_back(o+v*x+v.rot(ccw90)*y);
		s.push_back(o+v*x-v.rot(ccw90)*y);
		return s;
	}

	vector<pt> tang(pt p) {
		// cerr << p.x << " " << p.y << " - " << o.x << " " << o.y << " " << r << endl;
		assert((p-o).norm2() >= r*r+EPS);
		ld d=sqrt((p-o).norm2()-r*r);
		// ld d = (p-o).norm();
		// return *this^circle((p+o)/2.0,d/2.0);
		return *this^circle(p,d);
	}
};

struct ln {
	pt p, pq;
	ln(pt p, pt q): p(p), pq(q-p) {}
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit()) < EPS;}
	pt operator^(ln l) {
		if(*this/l) return nop;
		pt r = l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
		return r;
	}
};

ld inter(vector<pair<ld, int>> ev, ld s, ld e, int ind) {
	ev.push_back({s, 0});
	ev.push_back({e, 0});
	sort(ev.begin(), ev.end());
	ld last = s;
	int depth = ind;
	ld total = 0;
	for(auto p : ev) {
		ld x = p.first;
		x = max(x, s);
		x = min(x, e);
		// assert(depth >= 0);
		if(depth > 0) total += x-last;
		last = x;
		depth += p.second;
	}
	return total;
}

int main() {
	int p, c;
	ld x, y;
	while(cin >> p >> c >> x >> y && p != 0) {
		vector<pt> ps(p);
		for(pt &point : ps) cin >> point.x >> point.y;

		vector<circle> cs(c);
		for(circle &circ : cs) cin >> circ.o.x >> circ.o.y >> circ.r;

		ld total = 0;
		auto doit = [&]() {
			ln base = ln(pt(0, 0), pt(1, 0));
			vector<pair<ld, int>> ev;
			int inital = 0;
			for(pt point : ps) {
				for(circle circ : cs) {
					ld hi = circ.o.y + circ.r;
					ld lo = circ.o.y - circ.r;
					ld mid = point.y;
					if(mid < lo+EPS) continue;
						vector<pt> tangs = circ.tang(point);
						assert(tangs.size() == 2);
						// for(pt point : tangs)
							// cout << point.x << " " << point.y << endl;
						// cout << endl;
						ln l1 = ln(point, tangs[0]);
						ln l2 = ln(point, tangs[1]);
						ld a = (l1^base).x;
						ld b = (l2^base).x;
					if(mid < hi+EPS) {
						bool side = point.x < circ.o.x;
						ld gd = tangs[0].y < tangs[1].y ? a : b;
						if(!side) {
							ev.push_back({0, -1});
							ev.push_back({gd, 1});
						} else {
							ev.push_back({gd, -1});
							ev.push_back({x, 1});
						}
					} else {
						// ev.push_back({0, 1});
						ev.push_back({min(a, b), -1});
						ev.push_back({max(a, b), 1});
						// ev.push_back({x, -1});
					}
				}
			}
			cout << inital << endl;
			for(auto p : ev) cout << p.first << " " << p.second << endl;
			total += inter(ev, 0, x, p);
		};
		doit();
		for(circle &circ : cs) swap(circ.o.x, circ.o.y);
		for(pt & point : ps) swap(point.x, point.y);
		swap(x, y);
		doit();
		for(circle &circ : cs) {
			// circ.o.x=x-circ.o.x;
			circ.o.y=y-circ.o.y;
		}
		for(pt & point : ps) {
			// point.x = x-point.x;
			point.y = y-point.y;
		}
		doit();
		swap(x, y);
		doit();
		cout << "A " << total << endl;
	}
}
