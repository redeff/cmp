#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;

vector<ll> factor(ll n) {
	vector<ll> res;
	for(ll p = 2; p * p <= n; ++p) {
		if(n % p == 0) {
			res.push_back(p);
			while(n % p == 0) n /= p;
		}
	}
	if(n != 1) res.push_back(n);
	return res;
}

ll po(ll b, ll e) {
	ll res = 1;
	while(e != 0) {
		if(e % 2 == 1) {
			res *= b;
			res %= mod;
		}
		b *= b;
		b %= mod;
		e /= 2;
	}
	return res;
}

// sum v_p(i)
ll sum(ll p, ll n) {
	if(n < p) return 0;
	return n/p + sum(p, n/p);
}

int main() {
	ll x, n;
	cin >> x >> n;

	auto ps = factor(x);
	ll total = 1;
	for(ll p : ps) {
		total *= po(p, sum(p, n));
		total %= mod;
	}
	cout << total << endl;
}
