#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Point {
	ll x;
	ll y;
	ll len() {
		ll total = 0;
		if(x < 0) total -= x;
		else total += x;
		if(y < 0) total -= y;
		else total += y;
		return total;
	}
};

Point operator+(Point a, Point b) {
	return {a.x + b.x, a.y + b.y};
}

Point operator-(Point a, Point b) {
	return {a.x - b.x, a.y - b.y};
}

Point operator*(ll a, Point b) {
	return {a * b.x, a * b.y};
}

int main() {
	Point p1;
	Point p2;
	cin >> p1.x >> p1.y;
	cin >> p2.x >> p2.y;
	ll n;
	cin >> n;
	string s;
	cin >> s;

	p2 = p2 - p1;
	p1 = Point {0, 0};

	vector<Point> ns;
	for(char c : s) {
		switch (c) {
			case 'U':
				ns.push_back(Point {0, 1});
				break;
			case 'D':
				ns.push_back(Point {0, -1});
				break;
			case 'L':
				ns.push_back(Point {-1, 0});
				break;
			case 'R':
				ns.push_back(Point {1, 0});
				break;
		}
	}

	Point total = Point {0, 0} - accumulate(ns.begin(), ns.end(), Point {0, 0});
	
	ll lo = 0;
	ll hi = 1;
	
	function<int(ll)> can = [&](ll k) {
		ll tim = k * n;
		ll dist = (p2 + k * total).len();
		return dist - tim;
	};

	while(can(hi) > 0) {
		if(can(hi+1ll) == can(hi)) {
			cout << -1 << endl;
			return 0;
		}
		hi *= 2ll;
	}

	while(hi > lo + 1) {
		ll mid = (hi + lo) / 2ll;
		if(can(mid) > 0) lo = mid;
		else hi = mid;
	}

	ll res = -1;
	Point partial = Point {0, 0};
	for(int i = 0; i < 2 * n; ++i) {
		partial = partial - ns[i];
		ll tim = n * lo + i + 1ll;
		ll dist = (p2 + lo * total + partial).len();
		if(dist <= tim) {
			res = n * lo + i + 1ll;
			break;
		} else {
			// cerr << dist << endl;
			// cerr << tim << endl;
		}
	}

	cout << res << endl;
};
