#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll bound = 2e3 + 10;
vector<vector<ll>> dp(bound, vector<ll>(bound, 0));

ll rec(ll k, ll n, ll p) {
    if(k < bound && n < bound) return dp[k][n];
    if(k == 0 && n == 0) return 1;
    if(k > n) return 0;
    else if(k <= 0 || n <= 0) return 0;
    else {
        return (rec(k, n - k, p) + rec(k - 1, n - 1, p) + 1) % p;
    }
}

int main() {
    ll t, p;
    cin >> t >> p;

    // vector<vector<ll>> dp(bound, vector<ll>(bound, 0));
    dp[0][0] = 1;
    for(ll k = 0; k < bound; ++k) for(ll n = 0; n < bound; ++n) if(n != 0 || k != 0) {
        if(n - k >= 0) {
            dp[k][n] += dp[k][n - k];
            dp[k][k] %= p;
        }
        if(k - 1 >= 0 && n - 1 >= 0) {
            dp[k][n] += dp[k - 1][n - 1];
            dp[k][n] %= p;
        }
    }

    for(int i = 0; i < t; ++i) {
        ll k, n;
        cin >> k >> n;
        cout << rec(k, n + k, p) << endl;
    }
}
