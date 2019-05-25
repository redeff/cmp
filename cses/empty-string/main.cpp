#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7;

ll fact(int n) {
	static vector<ll> dp = {1};
	while(n >= dp.size()) {
		dp.push_back(dp.back() * dp.size() % mod);
	}
	return dp[n];
}

ll inv(ll n) {
	// ll orig = n;

	ll m = mod;

	ll x = 1ll;
	ll y = 0ll;
	while(n > 1) {
		ll q = n / m;

		n %= m;
		swap(n, m);

		x = x - q * y;
		swap(x, y);
	}
	if(x < 0) x += mod;

	// assert(x * orig % mod == 1ll);

	return x;
}

pair<ll, ll> choose(int n, int k) {
	ll q = fact(k) * fact(n-k) % mod;
	// return fact(n) * inv(q) % mod;
	return {fact(n), q};
}

int main() {
	// inv(18237);
	string s;
	cin >> s;

	int n = (int) s.size();
	if(n % 2 == 1) {
		cout << 0 << endl;
		return 0;
	}

	vector<vector<ll>> dp(n/2+1);
	dp[0] = vector<ll>(n+1, 1);
	for(int l = 2; l <= n; l += 2) {
		for(int i = 0; i + l <= n; ++i) {
			ll num = 0;
			ll den = 1;
			for(int j = i+1; j < i + l; j += 2) if(s[i] == s[j]) {
				int a = j - i + 1;
				int b = l - a;
				// assert(b > 0);
				auto val = choose(l/2, a/2);
				val.first = val.first * dp[b/2][j+1] % mod * dp[a/2-1][i+1] % mod;
				num = num * val.second % mod + den * val.first % mod;
				den = val.second * den % mod;
				// auto val = choose(l/2, a/2) * dp[b/2][j+1] % mod * dp[a/2-1][i+1] % mod;
				// dp[l/2].back() += val;
				// dp[l/2].back() %= mod;
			}
			dp[l/2].push_back(num * inv(den) % mod);
		}
	}
	/*
	for(auto v: dp) {
		for(ll i : v) cerr << i << " ";
		cerr << endl;
	}
	*/
	cout << dp.back().back() << endl;
}
