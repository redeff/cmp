#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7;

ll inv(ll n) {
	ll m = mod;

	ll x = 1;
	ll y = 0;

	while(n > 1) {
		ll q = n / m;
		n %= m;
		swap(n, m);

		x -= q * y;
		swap(x, y);
	}

	if(x < 0) x += mod;

	return x;
}

ll fact(int n) {
	static vector<ll> dp = {1};
	while(dp.size() <= n) {
		dp.push_back(dp.back() * dp.size() % mod);
	}

	return dp[n];
}

ll choose(int n, int k) {
	ll q = fact(n - k) * fact(k) % mod;
	return fact(n) * inv(q) % mod;
}


int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		cout << choose(a, b) << "\n";
	}
}
