#include <bits/stdc++.h>
#define forn(i, n) for(ll i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;
ll root;
ll mod;

ll po(ll e, ll p) {
	ll res = 1;
	while(p > 0) {
		if(p % 2) res *= e;
		res %= mod;
		e *= e;
		e %= mod;
		p /= 2;
	}
	return res;
}

ll inv(ll e) {
	return po(e, mod-2);
}

bool isprime(ll p) {
	if(p < 2) return false;
	for(ll i = 2; i*i <= p; ++i) if(p % i == 0 && i < p) return false;
	return true;
}

void setup(ll n) {
	// r^n = r
	// n | p-1
	// p-1 = en
	// p = en+1
	ll e;
	for(e = 1000000000ll/n; !isprime(e*n+1); ++e);
	ll p = e*n+1;
	mod = p;

	ll h = (p-1)/2;

	ll r;
	do {
		r = rand()%p;
	} while(po(r, h) != p-1);

	root = po(r, e);
	// cerr << root << endl;
}

ll eval(vector<ll> const &poly, ll x) {
	ll p = 1;
	ll total = 0;
	for(ll a : poly) {
		total += a*p;
		total %= mod;
		p*= x;
		p %= mod;
	}
	return total;
}

vector<ll> pointwise(vector<ll> const & poly) {
	ll n = ll(poly.size());
	vector<ll> out(n, 0);
	forn(i, n) {
		out[i] = eval(poly, po(root, i));
	}
	return out;
}

vector<ll> div(vector<ll> const &poly, ll k) {
	// assert(k >= 0);
	// assert(k < mod);
	// P(x) / (x-k)
	ll n = ll(poly.size());
	assert(n >= 2);
	vector<ll> out(n-1);
	ll left = 0;
	// cout << k << " - ";
	// for(ll i : poly) cout << i << " ";
	// cout << endl;
	forn(i, n-1) {
		// cerr << left << " L" << endl;
		out[n-i-2] = (poly[n-i-1] - left + mod) % mod;
		left = mod - k*out[n-i-2]%mod;
		left %= mod;
	}
	// cerr << left << endl;
	ll t = 19238ll;
	assert(eval(poly, t) == eval(out, t) * (t - k + mod) % mod);
	// cerr << left << endl;
	assert(left == poly[0]);
	return out;
}

vector<ll> prod(vector<ll> const &poly, ll k) {
	//P(x) * (x-k)
	ll n = ll(poly.size());
	vector<ll> out(n+1, 0);
	forn(i, n) {
		out[i] += mod - k*poly[i]%mod;
		out[i] %= mod;
		out[i+1] += poly[i];
		out[i+1] %= mod;
	}
	ll t = 18237;
	assert(eval(out, t) == eval(poly, t) * (t - k + mod) % mod);
	return out;
}

vector<ll> inter(vector<ll> const &points) {
	ll n = points.size();
	vector<ll> lagrange = {1};
	forn(i, n) lagrange = prod(lagrange, po(root, i));

	vector<ll> out(n, 0);
	forn(i, n) {
		auto d = div(lagrange, po(root, i));
		ll k = inv(eval(d, po(root, i))) * points[i];
		k %= mod;
		forn(j, n) {
			out[j] += d[j] * k;
			out[j] %= mod;
		}
	}
	assert(pointwise(out) == points);
	return out;
}

vector<ll> conv(vector<ll> a, vector<ll> b) {
	/*
	a = pointwise(a);
	b = pointwise(b);
	forn(i, a.size()) {
		a[i] *= b[i];
		a[i] %= mod;
	}

	return inter(a);
	*/
	vector<ll> res(a.size(), 0);
	forn(i, a.size()) forn(j, b.size()) {
		res[(i+j) % a.size()] += a[i] * b[j];
		// res[(i+j) % a.size()] %= mod;
	}
	return res;
}

bool caso(ll n, ll k) {
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<ll> ker(n);
	forn(i, n) ker[i] = i < k;

	// assert(inter(pointwise(ns)) == ns);
	auto pns = pointwise(ns);
	auto pker = pointwise(ker);

	forn(i, n) {
		pns[i] *= inv(pker[i]);
		pns[i] %= mod;
	}
	auto res = inter(pns);

	auto cnv = conv(ker, res);
	return cnv == ns;

	/*
	for(ll i : conv(ker, res)) cerr << i << " ";
	cerr << endl;
	*/


	/*
	for(ll i : res) cerr << i << " ";
	cerr << endl;
	*/
	for(ll i : res) if(i > 1e6) return false;
	return true;
}

int main() {
	int n, k;
	cin >> n >> k;
	setup(n);
	// cerr << mod << endl;
	if(caso(n, k)) cout << "S" << endl;
	else cout << "N" << endl;
}
