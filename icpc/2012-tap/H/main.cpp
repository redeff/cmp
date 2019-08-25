#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld eps = 1e-9;
ld inf = 1e10;

struct Vec {
	ld x;
	ld y;
};

struct Fun {
	ld m;
	ld c;
	int id;
};
// mx + c

bool zero(ld f) {
	return abs(f) < eps;
}

ld inter(Fun a, Fun b) {
	assert(!zero(a.m - b.m));
	return (b.c - a.c) / (a.m - b.m);
}

typedef pair<ld, ld> Range;
// Rango donde A le gana a B
Range range(Fun a, Fun b) {
	assert(a.id != b.id);
	if(zero(a.m - b.m)) {
		if(zero(a.c - b.c)) {
			if(a.id < b.id) return {-inf, inf};
			else return {inf, inf};
		} else {
			if(a.c > b.c) return {-inf, inf};
			else return {inf, inf};
		}
	} else {
		ld x = inter(a, b);
		if(a.m > b.m) return {x, inf};
		else return {-inf, x};
	}
}

Range inte(Range a, Range b) {
	Range r = {max(a.first, b.first), min(a.second, b.second)};
	if(r.first > r.second) return {inf, inf};
	return r;
}

struct Line {
	Fun f;
	Range r;
};

// El rango donde A le gana a B
Range inters(Line a, Line b) {
	Range r = range(a.f, b.f);
	return inte(r, inte(a.r, b.r));
}

Line through(ld x1, ld y1, ld x2, ld y2, int id) {
	Line out;
	out.f.m = (y2 - y1) / (x2 - x1);
	out.f.c = y1 - out.f.m * x1;

	out.r.first = min(x1, x2);
	out.r.second = max(x1, x2);

	out.f.id = id;
	return out;
}

ld eval(Fun a, ld x1, ld x2) {
	ld len = x2 - x1;
	ld y1 = x1 * a.m + a.c;
	ld y2 = x2 * a.m + a.c;
	ld res = len * (y1 + y2) / 2;
	assert(res >= 0);
	return res;
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		vector<Line> ns;
		ns.reserve(2*n);
		for(int i = 0; i < n; ++i) {
			ld l, r, h;
			cin >> l >> r >> h;
			ld m = (l + r) / 2;
			ns.push_back(through(l, 0, m, h, 2*i));
			ns.push_back(through(m, h, r, 0, 2*i+1));
		}

		ld total = 0;
		for(Line l : ns) {
			vector<pair<ld, int>> events;
			for(Line u : ns) if(u.f.id != l.f.id) {
				Range r = inters(u, l);
				events.emplace_back(r.first, -1);
				events.emplace_back(r.second, 1);
			}
			events.emplace_back(l.r.second, 0);
			sort(events.begin(), events.end());
			ld last = l.r.first;
			int cover = 0;
			for(auto p : events) {
				if(p.first - eps > l.r.second) continue;
				if(p.first + eps < l.r.first) assert(false);
				assert(cover >= 0);
				if(cover == 0) {
					ld e = eval(l.f, last, p.first);
					// cerr << "e " << e << endl;
					total += e;
				}
				last = p.first;
				cover -= p.second;
			}
		}

		cout << fixed;
		cout << setprecision(2);
		cout << total << endl;
	}
}
