#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7ll;

ll fact(int n) {
	static vector<ll> dp = {1ll};
	while(dp.size() <= n) {
		dp.push_back(dp.size() * dp.back() % mod);
	}
	return dp[n];
}

ll inv(ll n) {
	ll a = n;
	ll b = mod;
	ll c = 1;
	ll d = 0;
	while(true) {
		ll q = a/b;

		a = a - q * b;
		swap(a, b);
		if(b == 0) break;

		c = c - q * d;
		c %= mod;
		c += mod;
		c %= mod;
		swap(c, d);
	}

	return d;
}

ll choose(int n, int k) {
	ll prod = fact(k) * fact(n-k) % mod;
	return fact(n) * inv(prod) % mod;
}

ll ways(pair<int, int> a, pair<int, int> b) {
	int x = b.first - a.first;
	int y = b.second - a.second;
	if(x < 0 || y < 0) return 0;
	return choose(x+y, x);
}

int main() {
	/*
	assert(fact(0) == 1);
	assert(fact(1) == 1);
	assert(fact(2) == 2);
	assert(fact(3) == 6);
	assert(inv(1) == 1);
	assert(inv(33) * 33 % mod == 1);
	*/
	cin.tie(0);
	ios::sync_with_stdio(0);
	int l, n;
	cin >> l >> n;
	vector<pair<int, int>> ns(n+2);
	for(int i = 0; i < n; ++i) cin >> ns[i].first >> ns[i].second;
	ns[n] = {1, 1};
	ns[n+1] = {l, l};

	n = ns.size();
	sort(ns.begin(), ns.end());
	ns.erase(unique(ns.begin(), ns.end()), ns.end());
	vector<ll> dp(n);
	for(int i = 0; i < n; ++i) {
		dp[i] = ways(ns[0], ns[i]);
		for(int j = 1; j < i; ++j) {
			dp[i] += mod - dp[j] * ways(ns[j], ns[i]) % mod;
			dp[i] %= mod;
		}
	}

	cout << dp.back() << "\n";
}
