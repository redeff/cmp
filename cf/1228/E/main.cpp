#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = int(z); i < int(n); ++i)
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;

const int B = 270;
ll dp[B][B];

ll cho[B][B];

int main() {
	int n, k;
	cin >> n >> k;

	forn(i, 0, n+1) {
		cho[i][i] = 1;
		cho[i][0] = 1;
	}
	forn(i, 2, n+10) forn(j, 1, i) {
		cho[i][j] = cho[i-1][j] + cho[i-1][j-1];
		cho[i][j] %= mod;
	}

	vector<ll> pk = {1};
	vector<ll> pk1 = {1};

	forn(kjsdahf, 0, n+100) {
		pk.push_back(pk.back() * k % mod);
		pk1.push_back(pk1.back() * (k-1) % mod);
	}

	forn(i, 1, n+1) {
		dp[0][i] = pk1[n-i] * cho[n][i] % mod;
	}
	forn(i, 1, n) {
		forn(t, 1, n+1) {
			dp[i][t] = dp[i-1][t]
				* (mod + pk[t] - pk1[t]) % mod
				* pk1[n-t] % mod;
			forn(r, 1, t) {
				dp[i][t] += dp[i-1][r]
					* pk[r] % mod
					* pk1[n-t] % mod
					* cho[n-r][t-r] % mod;
				dp[i][t] %= mod;
			}
		}
	}

	cout << dp[n-1][n] << endl;
}
