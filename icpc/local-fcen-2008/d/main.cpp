#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Conn {
	int to;
	ll wei;
	bool operator<(const Conn b) const {
		return wei > b.wei;
	}
};

ll sq(ll a) {
	return a * a;
}

ll nor(pair<ll, ll> a, pair<ll, ll> b) {
	return sq(a.first - b.first) + sq(a.second - b.second);
}

const ll INF = 3333333333333333ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout.precision(3);
	cout << fixed;

	int n;
	ll h, w;
	while(cin >> n >> w >> h && n != -1) {
		vector<pair<ll, ll>> ns(n);

		for(auto &p : ns) {
			cin >> p.first >> p.second;
			// cerr << p.first << "~" << p.second << endl;
		}

		vector<ll> dist(n, INF);

		priority_queue<Conn> pq;
		for(int i = 0; i < n; ++i) {
			ll d = min(ns[i].first, h - ns[i].second);
			pq.push(Conn {i, 4*sq(d)});
		}
		while(!pq.empty()) {
			Conn c = pq.top(); pq.pop();
			if(c.wei >= dist[c.to]) continue;
			dist[c.to] = c.wei;
			for(int ch = 0; ch < n; ++ch) {
				ll d = nor(ns[ch], ns[c.to]);
				d = max(d, dist[c.to]);
				if(d < dist[ch]) pq.push(Conn {ch, d});
			}
		}

		// for(ll d : dist) cout << d << " ";
		// cout << endl;
		ll val = INF;
		for(int i = 0; i < n; ++i) {
			ll d = min(ns[i].second, w - ns[i].first);
			val = min(val, max(4*sq(d), dist[i]));
		}
		// double res = sqrt(val)/2.0 + 1e-9;
		val *= 500ll * 500ll;
		double res = round(sqrt(val)) / 1000.0;
		// cout << val << endl;
		cout << res << "\n";
		/*
		cout << res << endl;
		cout.precision(3);
		cout << fixed;
		cout << res << endl;
		*/
	}
}
