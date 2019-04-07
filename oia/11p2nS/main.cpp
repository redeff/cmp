#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, n) for(ll i = 0; i < n; ++i)

ll as(ll i) {
	return i > 0 ? i : -i;
}

int main() {
#ifndef LOLOLOL
	ifstream cin("bloques.in");
	ofstream cout("bloques.out");
#endif
	ll n, k;
	cin >> n >> k;

	vector<ll> ns(n);
	forn(i, n) cin >> ns[i];
	forn(i, n) {
		ll j;
		cin >> j;
		// cerr << j << endl;
		ns[i] -= j;
	}

	// for(ll s : ns) cerr << s << " ";
	// cerr << endl;

	vector<ll> sums(n, 0);
	sums[0] = ns[0];
	forn(i, n-1ll) sums[i+1ll] = sums[i] + ns[i+1ll];
	ll sum = sums.back();
	sums.pop_back();

	function<ll(ll)> cost = [&](ll t) {
		ll total = 0;
		for(ll i : sums) total += as(i - t);
		return total + k * as(t) + k * as(sum - t) ;
	};

	// ll lo = -as(sum);
	// ll hi = as(sum);
	ll lo = -33333333333ll;
	ll hi = 33333333333ll;
	// ll best = cost(0);
	// for(ll i = lo; i <= hi; ++i) best = min(best, cost(i));
	// cout << best << endl;
	while(lo < hi - 2ll) {
		ll a = (hi + 2ll*lo) / 3ll;
		ll b = (2ll*hi + lo) / 3ll;
		if(cost(a) < cost(b)) hi = b;
		else lo = a;
	}
	// for(ll i = -20; i < 20; ++i) cerr << cost(i) << " ";
	// cerr << sum << endl;
	cout << min(cost(lo), min(cost(lo+1ll), cost(hi))) << endl;
}
