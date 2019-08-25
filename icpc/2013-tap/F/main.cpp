#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld eps = 1e-9;

struct Point {
	ld x;
	ld y;
};

vector<Point> ns;
int n;
int target;

ld nor(ld ang) {
	while(ang > 2*M_PI) ang -= 2*M_PI;
	while(ang < 0) ang += 2*M_PI;
	return ang;
}

bool can_at(int root, double rad) {
	static vector<pair<ld, int>> ev;
	ev.clear();
	int curr = 0;
	for(int i = 0; i < n; ++i) if(i != root) {
		ld dx = ns[i].x - ns[root].x;
		ld dy = ns[i].y - ns[root].y;

		ld dist = hypot(dx, dy);
		if(dist >= 2*rad) continue;
		ld ang = atan2(dy, dx);
		ld co = acos(dist / (2*rad));
		ld pos = nor(ang + co);
		ld neg = nor(ang - co);
		// if(pos < M_PI - eps && neg > M_PI + eps) curr++;
		if(pos < neg) curr++;
		ev.emplace_back(neg, 1);
		ev.emplace_back(pos, -1);
	}

	sort(ev.begin(), ev.end());
	if(curr >= target - 1) return true;
	for(auto p : ev) {
		curr += p.second;
		if(curr >= target - 1) return true;
	}

	return false;
}

bool can(double rad) {
	for(int i = 0; i < n; ++i) {
		if(can_at(i, rad)) return true;
	}
	return false;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) {
		cin >> n >> target;
		ns = vector<Point>(n);
		for(Point & p : ns) cin >> p.x >> p.y;

		ld lo = 0;
		ld hi = 1e6;
		while(hi - lo > eps) {
			ld mid = (hi + lo) / 2.0;
			if(can(mid)) hi = mid;
			else lo = mid;
		}

		cout << fixed;
		cout << setprecision(4);
		cout << lo << endl;
	}
}
