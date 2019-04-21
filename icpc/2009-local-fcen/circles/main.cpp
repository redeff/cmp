#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Circle {
	double x;
	double y;
	double r;
};

double dist(Circle a, Circle b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	double d = sqrt(x*x + y*y);
	double t = sqrt(d*d - (a.r - b.r) * (a.r - b.r));
	return 2*t + 2 * b.r * acos((a.r - b.r)/d) + 2 * a.r * acos((b.r - a.r)/d);
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		vector<Circle> ns(n);
		for(auto &c : ns) cin >> c.x >> c.y >> c.r;
		priority_queue<pair<double, int>> pq;
		vector<bool> seen(n, false);
		pq.push({0, 0});

		double total = 0.0;
		while(!pq.empty()) {
			auto p = pq.top().second;
			auto w = pq.top().first;
			pq.pop();
			if(!seen[p]) {
				seen[p] = true;
				total -= w;
				for(int i = 0; i < n; ++i) if(i != p) {
					pq.push({-dist(ns[p], ns[i]), i});
				}
			}
		}
		ll res = ceil(total * 1000.0 - 0.5);
		// cout.fixed = 3;
		// cout.precision(3);
		cout << res / 1000ll << "." << res % 1000ll / 100ll << res % 100ll / 10ll << res % 10ll << endl;
	}
}
