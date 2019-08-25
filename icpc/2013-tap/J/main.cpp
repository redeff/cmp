#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;

int main() {
	int tot = 1100;
	// cin >> tot;
	// tot++;

	vector<vector<ll>> dp(tot, vector<ll>(tot, 1));
	for(int n = 0; n < tot; ++n) {
		for(int k = n+1; k < tot; ++k) {
			dp[n][k] = 0;
		}
	}
	for(int n = 2; n < tot; ++n) for(int k = 2; k < n; ++k) {
		dp[n][k] = (dp[n-k][k] + dp[n-1][k-1]) % mod;
	}


	int t;
	cin >> t;
	while(t --> 0) {
		int tot;
		cin >> tot;
		++tot;
		ll total = 0;
		for(int k = 1; k < tot; ++k) {
			if(k % 2 == tot % 2) {
				total += dp[tot-1][k];
				total %= mod;
			}
		}

		cout << total << endl;
	}
}
