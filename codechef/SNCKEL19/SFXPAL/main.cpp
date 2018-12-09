#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    ll n, s, MOD;
    cin >> n >> s >> MOD;

    vector<ll> dp(n+30, -2);
    // dp[2] = s * (s - 1) % MOD;
    dp[1] = s % MOD;
    dp[0] = 1;

    for(int i = 2; i < dp.size(); ++i) {
        dp[i] = dp[i-1] * s % MOD;
        dp[i] -= dp[(i+1)/2];
        dp[i] %= MOD;
        dp[i] += MOD;
        dp[i] %= MOD;
    }

    cout << dp[n] << endl;
}
