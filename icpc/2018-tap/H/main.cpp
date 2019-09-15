#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld EPS = 1e-9;
ld inf = numeric_limits<ld>::infinity();

struct pt {
	ld x;
	ld y;

	pt(): x(0), y(0) {}
	pt(ld x, ld y): x(x), y(y) {}

	bool operator==(pt p) const {
		return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
	}

	pt operator+(pt p) {
		return pt(x + p.x, y + p.y);
	}

	pt operator-(pt p) {
		return pt(x - p.x, y - p.y);
	}

	ld operator*(pt p) {
		return x*p.x + y*p.y;
	}

	pt operator*(ld t) {
		return pt(x*t, y*t);
	}

	ld operator%(pt p) {
		return x*p.y - y*p.x;
	}

	ld norm2() {return *this**this;}
	ld norm() {return sqrt(norm2());}
	pt unit() {return *this*(1.0/norm());}

	pt rot(pt r) {return pt(*this%r, *this*r);}
};

pt ccw90(1, 0);

pt no(2734987.123, 12823948.45);

struct ln {
	pt p, pq;
	
	bool operator/(ln l) {return abs(pq.unit()%l.pq.unit()) < EPS;}
	pt operator^(ln l) {
		if(*this/l) return no;
		pt r = l.p + l.pq * ((p-l.p) % pq / (l.pq%pq));
		return r;
	}
};

ln med(pt a, pt b) {
	pt mid = (a + b) * 0.5;
	return ln{mid, (a-b).rot(ccw90)};
}

pt circ(pt a, pt b, pt c) {
	return med(a, b) ^ med(b, c);
}

int main() {
	int n;
	cin >> n;

	vector<pt> ns(n);
	for(pt &p : ns) cin >> p.x >> p.y;

	srand(847298734);
	ld best = -1;

	auto use = [&](pt o) {
		ld a = -1, b = -1;
		for(pt p : ns) {
			ld c = (p-o).norm();

			if(a == -1) a = c;
			if(abs(a-c) < EPS) continue;

			if(b == -1) b = c;
			if(abs(b-c) < EPS) continue;

			goto failed;
		}

		if(b == -1) {
			best = inf;
		} else {
			best = max(best, 0.5 * abs(a - b));
		}
failed:;
	};

	if(n >= 3) {
		for(int lala = 0; lala < 100000; ++lala) {
			int i = 2 + rand()%(n-2);
			int j = 1 + rand()%(i-1);
			int k = 0 + rand()%(j-0);

			pt o = circ(ns[i], ns[j], ns[k]);
			use(o);
		}
	}

	if(n <= 10) {
		for(int i = 0; i < n; ++i) {
			use(ns[i]);
			for(int j = 0; j < n; ++j) {
				use((ns[i] + ns[j]) * 0.5);
				for(int k = 0; k < n; ++k) for(int l = 0; l < n; ++l) {
					pt p = med(ns[i], ns[j]) ^ med(ns[k], ns[l]);
					use(p);
				}
			}
		}
	}

	if(best == -1) cout << "NO";
	else if(best == inf) cout << "INF";
	else cout << setprecision(2) << fixed << best;
	cout << endl;
}
