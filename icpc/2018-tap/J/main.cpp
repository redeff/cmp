#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;
// ll mod = (1ll << 62ll) + 1ll;

ll sigma = 'z' - 'a' + 1;
ll diff(string s) {
	vector<bool> seen(sigma, false);
	for(char c : s) seen[c-'a'] = true;
	return accumulate(seen.begin(), seen.end(), 0ll);
}

ll po(ll b, ll e) {
	if(e < 0) return 0;
	ll res = 1;
	ll tot = 1;
	for(int i = 0; i < e; ++i) {
		res *= b;
		res %= mod;
		tot += res;
		tot %= mod;
	}

	// cout << b << "^" << e << " = " << res << endl;
	// cout << b << "^" << e << " -> " << tot << endl;
	return tot;
}

ll choose(ll, ll);
ll choose_bad(ll n, ll k) {
	if(k == 0) return 1;
	if(k == n) return 1;
	if(k > n) return 0;
	return (choose(n-1, k) + choose(n-1, k-1)) % mod;
}

ll choose(ll n, ll k) {
	static vector<vector<ll>> dp = {{1}};
	while(n >= dp.size()) {
		dp.push_back(dp.back());
		dp.back().push_back(0);
		for(int i = 1; i < dp.back().size(); ++i) {
			dp.back()[i] += dp[dp.size()-2][i-1];
			dp.back()[i] %= mod;
		}
	}

	if(k > n) return 0;
	// cout << n << " " << k << " -> " << dp[n][k] << endl;
	return dp[n][k];
}

ll prob(ll k, ll n) {
	assert(k <= n);
	ll total = 0;
	for(int i = 0; i < k; i += 2) {
		for(int j = i; j < k; ++j) {
			ll delta = choose(j, i) + choose(j, i) * (sigma-k+j+1) * po(sigma, n - i - 2);
			total += delta;
			total %= mod;
		}
	}
	return total;
}

int main() {
	ll n;
	cin >> n;
	string s;
	cin >> s;

	ll k = diff(s);
	cout << prob(k, n) << endl;
}
