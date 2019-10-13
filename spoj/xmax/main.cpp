#include <bits/stdc++.h>
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define forz(i, z, n) for(ll i = z; i < n; ++i)
using namespace std;
typedef unsigned long long int ll;
const ll p = 64;

int main() {
	ll n;
	cin >> n;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	ll base = 0;
	forn(x, p) {
		ll e = p-x-1;
		ll index = n;
		forz(i, base, n) {
			if(ns[i] & (1ll << e)) index = i;
		}
		if(index != n) {
			if(base != index) swap(ns[base], ns[index]);
			base++;
			forz(i, base, n) {
				if(ns[i] & (1ll << e)) ns[i] ^= ns[base-1];
			}
		}
	}
	// reverse(ns.begin(), ns.end());

	/*
	forn(i, n-1) {
		cerr << bitset<p>(ns[i]) << endl;
		// assert((ns[i+1] ^ ns[i]) >= ns[i+1]);
		if(ns[i] != 0 && ns[i+1] != 0) {
			assert(__builtin_clzl(ns[i]) < __builtin_clzl(ns[i+1]));
		} else {
			if(ns[i] == 0) assert(ns[i+1] == 0);
		}
	}
	*/

	ll total = 0;
	forn(i, n) if((total ^ ns[i]) > total) total ^= ns[i];
	cout << total << endl;
}
