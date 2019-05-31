#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll mod = 1e9+7;

int main() {
	int n;
	cin >> n;

	ll sum = n * (n+1) / 2;
	if(sum % 2 != 0) {
		cout << 0 << endl;
	} else {
		vector<ll> dp(sum/2+1, 0);
		dp[0] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = dp.size()-1; j >= i; --j)
				dp[j] = (dp[j] + dp[j-i]) % mod;
		}
		ll res = dp.back();
		if(res % 2 == 1) res += mod;
		res /= 2;
		res %= mod;
		cout << res << endl;
	}
}
