#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int k = 50;

struct Point {
	int x;
	int y;
};

pair<int, int> sq(Point p, double d) {
	return {floor(double(p.x) / d), floor(double(p.y) / d)};
}

ll hs(pair<int, int> p) {
	return p.first + (p.second << 30);
}

double dist(Point a, Point b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x*x + y*y);
}

double per(Point a, Point b, Point c) {
	return dist(a, b) + dist(b, c) + dist(c, a);
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		vector<Point> ns(n);
		for(Point &p : ns) cin >> p.x >> p.y;
		double hi = 100000000.0;
		for(int i = 0; i < int(ns.size()); ++i) {
			for(int j = 0; j < i; ++j) if(2.0 * dist(ns[i], ns[j]) < hi) {
				for(int l = 0; l < j; ++l) {
					hi = min(hi, per(ns[i], ns[j], ns[l]));
				}
			}
		}
		ll res = floor(hi * 1000.0 + 0.5001);
		// cout.fixed = 3;
		// cout.precision(3);
		cout << res / 1000ll << "." << res % 1000ll / 100ll << res % 100ll / 10ll << res % 10ll << endl;
		// cout << hi << endl;
		// cout.precision(13);
		// cout << lo << endl;
	}
}
