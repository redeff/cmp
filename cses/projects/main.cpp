#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Proj {
	ll a;
	ll b;
	ll p;
};

bool operator<(Proj a, Proj b) {
	// return make_tuple(a, b) < make_tuple(a, b);
	return a.a < b.a;
}

int main() {
	int n;
	cin >> n;

	vector<Proj> ns(n);

	for(int i = 0; i < n; ++i) {
		cin >> ns[i].a >> ns[i].b >> ns[i].p;
		// ns[i].b++;
	}
	sort(ns.begin(), ns.end());

	map<ll, ll> dp;
	dp.insert({-11283, 0});
	for(Proj p : ns) {
		auto it = prev(dp.lower_bound(p.a));
		ll val = it->second + p.p;

		auto et = prev(dp.lower_bound(p.b));
		if(et->second >= val) continue;
		dp[p.b] = max(val, dp[p.b]);

		while(true) {
			auto ot = dp.upper_bound(p.b);
			if(ot == dp.end()) break;
			if(ot->second > val) break;
			else dp.erase(ot);
		}
	}

	cout << dp.rbegin()->second << endl;
}
