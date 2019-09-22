#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

typedef long long int ll;
const ll n = 1e6+100;
const ll mod = 998244353;

ll po(ll base, ll e) {
	ll res = 1;
	while(e != 0) {
		if(e % 2 == 1) {
			res *= base;
			res %= mod;
		}
		base *= base;
		base %= mod;
		e /= 2;
	}
	return res;
}

ll inv(ll k) {
	k %= mod;
	assert(k != 0);
	ll res = po(k, mod-2);
	assert(res*k%mod == 1);
	return res;
}

int main() {
	vector<ll> ns(n, 0);
	{
		int m;
		cin >> m;
		forn(i, 0, m) {
			ll k;
			cin >> k;
			ns[k]++;
		}
	}

	vector<ll> factor(n, 0);
	ll total = 0;
	forn(g, 1, n) {
		ll k = factor[g] + inv(g);
		k %= mod;

		ll sum = 0;
		for(ll i = 0; i < n; i += g) {
			sum += i*ns[i];
			sum %= mod;
			factor[i] += mod - k;
			factor[i] %= mod;
		}
		sum %= mod;
		sum *= sum;
		sum %= mod;

		total += sum * k;
		total += mod - (ns[g] * g) % mod;
		total %= mod;
	}

	total *= inv(2);
	total %= mod;

	cout << total << endl;
}
