#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;

ll norm2(pair<ll, ll> a, pair<ll, ll> b) {
	ll dx = a.first - b.first;
	ll dy = a.second - b.second;
	return dx*dx + dy*dy;
}

int main() {
	int n;
	cin >> n;

	vector<pair<ll, ll>> ns(n);
	for(auto &p : ns) cin >> p.first >> p.second;

	int total = 0;
	forn(i, n) forn(j, i) forn(k, j) {
		ll a = norm2(ns[i], ns[j]);
		ll b = norm2(ns[j], ns[k]);
		ll c = norm2(ns[k], ns[i]);

		ll mx = max(a, max(b, c));
		if(a + b + c == 2*mx) total++;
	}

	cout << total << endl;
}
