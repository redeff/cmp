#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;
ll inf = 33333333333333;

ll cto(ll num) {
	ll total = 0;
	while(num%2 == 1) {
		num /= 2;
		total++;
	}
	return total;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	ll n;
	cin >> n;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<ll> ones(n);
	forn(i, n) ones[i] = cto(ns[i]);
	sort(ones.begin(), ones.end());

	bool cat = false;
	forn(i, n) if(ns[i] % 4 == 0) cat = true;

	ll sum = 0;
	ll best = inf;
	forn(k, n+1) {
		if(k != 0) sum += ones[k-1];
		ll left = n-k;

		if(left == 0 && sum == 0)
			best = min(best, 0ll);
		if(left <= sum && left != 0)
			best = min(best, sum);
		if(sum <= left && sum != 0)
			best = min(best, left);
		if(sum == 0 && left != n && cat)
			best = min(best, left);
		if(sum == 0 && left > 1)
			best = min(best, left+1);
	}

	assert(best != inf);

	cout << best << endl;
}
