#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll inf = 847513298457293ll;

ll n, r, k;

struct Frog {
	vector<ll> jumps;
	ll sum;
	ll init;
};

ll gcd(ll a, ll b) {
	while(b != 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

ll inv(ll e, ll mod) {
	e %= mod;
	e += mod;
	e %= mod;
	assert(gcd(e, mod) == 1);
	assert(e != 0);
	ll a = e;
	ll b = mod;

	ll x = 0;
	ll xx = 1;

	ll y = 1;
	ll yy = 0;
	while(b != 0) {
		ll quo = a/b;

		a -= quo*b;
		swap(a, b);

		xx -= quo*x;
		swap(x, xx);

		yy -= quo*y;
		swap(y, yy);
	}
	// cerr << yy * e + xx * mod << endl;
	assert(xx * e + yy * mod == 1);
	xx %= mod;
	xx += mod;
	xx %= mod;
	// cerr << xx << " " << e << " " << mod << endl;
	assert((xx * e) % mod == 1);
	return xx;
}

ll inter(Frog a, Frog b, ll t) {
	// r(a.sum - b.sum) == a.init - b.init + a.jumps[i] - b.jumps[i]  (mod n)
	// r*k + i >= t
	ll s = a.sum - b.sum;
	s %= n;
	s += n;
	s %= n;
	// cerr << "sum " << s << endl;
	ll mod = n;
	ll g = gcd(s, mod);
	if(s != 0) {
		mod /= g;
		s /= g;
		s = inv(s, mod);
	} else {
		g = mod;
		mod  = 1;
	}

	ll best = inf;
	for(int i = 0; i < k; ++i) {
		ll d = a.init - b.init + a.jumps[i] - b.jumps[i];
		d = -d;
		if(d % g != 0) continue;
		d /= g;
		d %= mod;
		d += mod;
		d %= mod;
		ll r = (d * s) % mod;

		// r*k + i >= t
		// r*k >= t - i
		// r >= (t - i) / k
		while(r*k + i < t) r += mod;
		// (r + l*mod)*k + i >= t
		// r + l*mod >=
		// cerr << d << " " << mod << " " << i << " " << s << " " << k << " " << r << endl;
		// cerr << "AAAH " << r*k+i << endl;
		best = min(best, r*k+i);
	}

	// cerr << best << endl;
	return best;
}

int main() {
	while(cin >> n >> r >> k) {
		vector<Frog> frogs(r);
		for(Frog &frog : frogs) cin >> frog.init;
		for(Frog &frog : frogs) {
			frog.jumps = vector<ll>(k);
			for(ll &j : frog.jumps) cin >> j;
			for(int i = 1; i < k; ++i) frog.jumps[i] += frog.jumps[i-1];
			frog.sum = frog.jumps.back();
			for(int i = k-1; i > 0; --i) frog.jumps[i] = frog.jumps[i-1];
			frog.jumps[0] = 0; } vector<ll> dist(r, inf);
		vector<ll> cmp(r, inf);

		dist[0] = 0;
		cmp[0] = 0;

		ll mxtime = 0;
		ll total = 0;
		for(int lala = 0; lala < r; ++lala) {
			int index = min_element(cmp.begin(), cmp.end()) - cmp.begin();
			if(cmp[index] < inf/2) {
				total++;
				mxtime = cmp[index];
			}
			cmp[index] = inf;
			for(int i = 0; i < r; ++i) if(dist[i] == cmp[i]) {
				dist[i] = min(dist[i], inter(frogs[index], frogs[i], dist[index]));
				cmp[i] = dist[i];
			}
		}

		cout << total << " " << mxtime << endl;
	}
}
