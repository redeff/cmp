#include <bits/stdc++.h>
using namespace std;

const int bound = 4000;

typedef long double ld;
ld dp[bound][bound][2];
ld inf = numeric_limits<ld>::infinity();
ld dist(pair<ld, ld> a, pair<ld, ld> b) {
	ld dx = a.first - b.first;
	ld dy = a.second - b.second;
	// cerr << dx << " " << dy << endl;
	ld d = sqrt(dx*dx + dy*dy);
	// cerr << "dist: " << d << endl;
	return d;
}

int main() {
	int n, s, e;
	while(cin >> n >> s >> e) {
		--s; --e;
		if(s > e) swap(s, e);
		vector<pair<ld, ld>> ns(n);
		for(auto &p : ns) cin >> p.first >> p.second;

		int a = e - s;
		int b = n - a;
		++a; ++b;

		for(int x = 0; x < a; ++x) for(int y = 0; y < b; ++y) {
			for(int i = 0; i < 2; ++i) dp[x][y][i] = inf;
		}

		dp[0][0][0] = 0;
		dp[0][0][1] = 0;

		for(int t = 0; t <= a+b; ++t) for(int k = 0; k <= t; ++k) {
			int x = k;
			int y = t - k;
			if(x >= a || y >= b) continue;

			int c = s + x;
			assert(c < n);
			int d = s - y;
			if(d < 0) d += n;
			if(y == b-1) assert(d == e);
			if(x == a-1) assert(c == e);

			int pc = s + x - 1;
			int pd = s - y + 1;
			if(pd < 0) pd += n;

			if(x != 0) dp[x][y][0] = dp[x-1][y][0] + dist(ns[pc], ns[c]);
			if(y != 0) dp[x][y][1] = dp[x][y-1][1] + dist(ns[pd], ns[d]);

			if(x != 0) dp[x][y][0] = min(dp[x][y][0], dp[x-1][y][1] + dist(ns[c], ns[d]));
			if(y != 0) dp[x][y][1] = min(dp[x][y][1], dp[x][y-1][0] + dist(ns[c], ns[d]));
		}

		cout << fixed << setprecision(6);
		cout << dp[a-1][b-1][1] << endl;
	}
}
