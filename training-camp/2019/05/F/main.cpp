#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll mod = 1000000007;

ll ex(ll b, ll e) {
	ll out = 1;
	while(e) {
		if(e%2 == 1) {
			out *= b;
			out %= mod;
		}
		b *= b;
		b %= mod;
		e /= 2;
	}
	return out;
}

ll inv(ll a) {
	return ex(a, mod-2);
}

vector<ll> coeffs(vector<ll> ns) {
	ll n = ns.size();
	// for(ll &i : ns) i = 
	vector<ll> out(n);
	for(ll i = 0; i < n; ++i) {
		out[i] = 1;
		for(ll j = 0; j < n; ++j) if(j != i) {
			out[i] *= mod + i - j;
			out[i] %= mod;
		}
		out[i] = inv(out[i]);
		out[i] *= ns[i] % mod;
		out[i] %= mod;
		out[i] += mod;
		out[i] %= mod;
	}

	return out;
}

ll eval(vector<ll> ns, vector<ll> coef, ll p) {
	p %= mod;
	ll total = 0;
	ll n = ns.size();
	for(ll i = 0; i < n; ++i) {
		ll term = coef[i];
		for(ll j = 0; j < n; ++j) if(j != i) {
			term *= mod + (p - j) % mod;
			term %= mod;
		}
		total += term;
		total %= mod;
	}
	return total;
}

int main() {
	ll n, k;
	cin >> n >> k;
	vector<ll> ns(k+2);
	ns[0] = 0;
	for(ll i = 1; i < k+2; ++i) {
		ns[i] = ns[i-1] + ex(i, k);
		ns[i] %= mod;
	}

	auto coef = coeffs(ns);
	ll res = eval(ns, coef, n);
	cout << res << endl;
}
