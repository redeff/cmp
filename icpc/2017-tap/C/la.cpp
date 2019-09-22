#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
#define forr(i, n) for(int i = n-1; i >= 0; --i)
using namespace std;

typedef long long int ll;
ll mod;
vector<ll> roots;

bool is_prime(ll p) {
	if(p < 2) return false;
	for(ll i = 2; i * i <= p; ++i) if(p % i == 0) return false;
	return true;
}

ll po(ll b, ll e) {
	assert(e >= 0);

	ll res = 1;
	while(e > 0) {
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

ll inv(ll b) {
	ll i = po(b, mod-2);
	// assert(i*b % mod == 1);
	return i;
}

vector<ll> primes(ll n) {
	vector<ll> total;
	for(ll i = 2; i * i <= n; ++i) if(n % i == 0) {
		// cerr << i << endl;
		assert(is_prime(i));
		total.push_back(i);
		while(n % i == 0) n /= i;
	}
	assert(is_prime(n));
	if(n != 1) total.push_back(n);
	return total;
}

void setup(ll n) {
	ll e = (2000000 + n)/n;
	while(!is_prime(e*n+1)) ++e;

	vector<ll> ps = primes(n*e);

	ll p = n*e+1;
	assert(is_prime(p));
	assert(p != 2);
	mod = p;
	// cerr << p << endl;

	srand(87249582);
	ll root = 0;
	while(true) {
		root = root+1;
		if(po(root, n*e) != 1) continue;
		for(ll pr : ps) {
			if(po(root, n*e/pr) == 1) goto cont;
		}
		break;
cont:;
	}

	assert(po(root, p) == root);
	assert(po(root, (p-1)/2) == p-1);
	assert(po(root, p-1) == 1);
	root = po(root, e);
	assert(po(root, n) == 1);

	// cerr << p << " " << root << endl;

	roots = vector<ll>(n);
	roots[0] = 1;
	forn(i, n-1) {
		roots[i+1] = (roots[i] * root) % mod;
		// assert(po(root, i+1) != 1);
		if(roots[i+1] == 1) {
			for(ll pr : ps) cout << pr << " ";
			cout << endl;
			cerr << i << " " << p << " " << root << endl;
			assert(false);
		}
	}
}

ll eval(vector<ll> const &poly, ll x) {
	ll res = 0;
	ll p = 1;
	forn(i, poly.size()) {
		res += poly[i] * p;
		res %= mod;

		p *= x;
		p %= mod;
	}

	return res;
}

vector<ll> pointwise(vector<ll> const &poly) {
	vector<ll> out(poly.size());
	forn(i, poly.size()) out[i] = eval(poly, roots[i]);
	return out;
}

vector<ll> division(vector<ll> const &poly, ll k) {
	vector<ll> out(poly.size()-1);
	ll left = 0;
	forr(i, poly.size()-1) {
		out[i] = poly[i+1] + mod - left;
		out[i] %= mod;

		left = out[i]*(mod-k);
		left %= mod;
	}
	// assert(left == poly[0]);
	return out;
}

vector<ll> product(vector<ll> const &poly, ll k) {
	vector<ll> out(poly.size()+1, 0);
	forn(i, poly.size()) {
		out[i] += mod-poly[i]*k;
		out[i] %= mod;

		out[i+1] += poly[i];
		out[i+1] %= mod;
	}
	return out;
}

vector<ll> interpolation(vector<ll> const &points) {
	vector<ll> lagrange = {1};
	forn(i, points.size()) {
		lagrange = product(lagrange, roots[i]);
		// assert(division(product(lagrange, 5), 5) == lagrange);
	}

	vector<ll> out(points.size(), 0);
	forn(i, points.size()) {
		vector<ll> d = division(lagrange, roots[i]);
		ll k = inv(eval(d, roots[i])) * points[i] % mod;
		forn(j, points.size()) {
			out[j] += d[j] * k;
			out[j] %= mod;
		}
	}
	// assert(pointwise(out) == points);
	return out;
}

vector<ll> conv(vector<ll> a, vector<ll> b) {
	vector<ll> out(a.size(), 0);

	forn(i, a.size()) forn(j, a.size()) {
		out[(i+j) % a.size()] += a[i] * b[j];
	}

	return out;
}

vector<ll> point_div(vector<ll> a, vector<ll> b) {
	forn(i, a.size()) {
		a[i] *= inv(b[i]);
		a[i] %= mod;
	}
	return a;
}

bool caso() {
	/*
	for(int i = 1; i < 100000; i += 10) {
		setup(i);
	}
	*/
	ll n, k;
	cin >> n >> k;
	setup(n);

	vector<ll> ns(n);
	for(ll &i : ns) {
		cin >> i;
		i %= mod;
	}

	vector<ll> ker(n);
	forn(i, n) ker[i] = i < k;

	auto cnv = conv(ker, interpolation(point_div(pointwise(ns), pointwise(ker))));
	// for(ll i : cnv) cout << i << " ";
	// cout << endl;
	return ns == cnv;
}

int main() {
	cout << (caso() ? "S" : "N") << endl;
}
