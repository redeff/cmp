#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll INF = 333333333333ll;

int main() {
	ll n, h;
	while(cin >> n >> h && n != -1) {
		n--;
		vector<ll> ns(n);
		for(auto & i : ns) cin >> i;

		vector<ll> sums(n+1, 0);
		for(int i = 0; i < n; ++i) {
			sums[i+1] = sums[i] + ns[i];
		}


		vector<ll> dp(n+1, INF);
		dp.back() = 0;
		for(ll i = n-1; i >= 0; --i) {
			for(ll j = i+1; j <= n; ++j) {
				if(sums[j] - sums[i] <= (j - i) * h) {
					dp[i] = min(dp[i], dp[j] + j - i - 1);
				}
			}
		}

		if(dp[0] >= INF / 2ll) dp[0] = -1;
		cout << dp[0] << endl;
	}
}
