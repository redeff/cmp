#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

#define fore(i, z, n) for(ll i = z; i < ll(n); ++i)

ll caso(ll n, ll k, ll l, int p[]) {
	vector<ll> side[2];
	fore(i, 0, n) if(p[i] != 0) {
		if(p[i] <= l/2) side[1].push_back(p[i]);
		else side[0].push_back(p[i]);
	}

	for(ll &i : side[0]) i = l - i;
	fore(i, 0, 2) {
		sort(side[i].begin(), side[i].end());
	}

	vector<ll> rems[2];
	fore(s, 0, 2) rems[s] = vector<ll>(k, 0);
	ll total = 0;

	fore(s, 0, 2) {
		ll last = 0;
		fore(i, 0, side[s].size()) {
			ll left = ll(side[s].size()) - i;
			ll rem = (left - 1 + k) % k;
			ll dist = side[s][i] - last;
			rems[s][rem] += dist;
			last += dist;
			total += dist * ((left + k - 1)/k);
		}
	}

	fore(s, 0, 2) {
		fore(i, 1, k) {
			rems[s][i] += rems[s][i-1];
		}
	}

	ll best = 0;
	fore(i, 1, k) {
		// i en uno, k-i en el otro
		best = max(best, rems[0][i-1] + rems[1][k-i-1]);
	}

	ll res = min(2*total, 2*total - 2*best + l);
	// int res = total;
	// cerr << res << endl;
	return res;
}

long long delivery(int n, int k, int l, int p[]) {
	long long a = caso(n, k, l, p);
	fore(i, 1, n) p[i] = l - p[i];
	a = min(a, caso(n, k, l, p));
	return a;
}
