#include <bits/stdc++.h>
#define forn(i, n) for(ll i = 0; i < n; ++i)
using namespace std;

long long int typedef ll;

bool isprime(ll p) {
	if(p < 2) return false;
	for(ll i = 2; i*i <= p; ++i) if(p%i == 0) return false;
	return true;
}

vector<ll> primes(ll n) {
	vector<ll> out;
	for(ll i = 2; i*i <= n; ++i) if(n%i == 0) {
		assert(isprime(i));
		out.push_back(i);
		while(n%i == 0) n /= i;
	}
	if(n != 1) {
		assert(isprime(n));
		out.push_back(n);
	}
	return out;
}

ll po(ll base, ll ex, ll mod) {
	ll res = 1;
	while(ex != 0) {
		if(ex % 2 == 1) {
			res *= base;
			res %= mod;
		}
		base *= base;
		base %= mod;
		ex /= 2;
	}
	return res;
}

// Returns prime and nth root of unity
pair<ll, ll> init(ll n, ll bound) {
	ll e = (n+bound)/n;
	while(!isprime(e*n+1)) ++e;
	ll p = e*n+1;
	auto ps = primes(p-1);

	ll root = 0;
	while(true) {
		++root;
		for(ll pr : ps) if(po(root, (p-1)/pr, p) == 1) goto notroot;
		break;
notroot:;
	}

	assert(root < p);
	assert(root != 0);

	return {p, po(root, e, p)};
}

vector<ll> fft(vector<ll> ns, ll root, ll p) {
	int n = int(ns.size());
	vector<ll> out(n, 0);
	forn(i, n) forn(j, n) {
		out[i] += ns[j] * po(root, i*j, p);
		out[i] %= p;
	}
	return out;
}

bool caso() {
	ll n, k;
	cin >> n >> k;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<ll> ds(n);
	forn(i, n) ds[i] = i < k;

	auto pr = init(n, *max_element(ns.begin(), ns.end()) + 100);
	ll p = pr.first;
	ll root = pr.second;

	assert(po(root, n, p) == 1);

	auto fns = fft(ns, root, p);
	auto fds = fft(ds, root, p);
	forn(i, n) {
		if(fds[i] == 0 && fns[i] != 0) {
			return false;
		}
		else if(fds[i] != 0) {
			fns[i] *= po(fds[i], p-2, p);
			fns[i] %= p;
		}
	}

	auto res = fft(fns, po(root, p-2, p), p);
	for(ll &i : res) {
		i *= po(n, p-2, p);
		i %= p;
	}
	vector<ll> orig(n, 0);
	forn(i, n) forn(j, k) {
		orig[(i+j)%n] += res[i] * ds[j];
		// orig[(i+j)%n] %= p;
	}

	return orig == ns;
}

int main() {
	cout << (caso() ? "S" : "N") << endl;
}
