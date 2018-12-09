#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll MOD = 1000000007;

vector<ll> divs(ll n) {
    if(n == 1) return {1};
    if(n == 2) return {2, 1};
    if(n == 3) return {3, 1};
    if(n == 4) return {4, 2, 1};
    vector<ll> out;
    ll srt = 0;
    for(ll d = 1; d * d <= n; ++d) if(n % d == 0) {
        out.push_back(n/d); 
        if(d * d < n) srt = d;
    }
    for(ll d = srt; d >= 1; --d) if(n % d == 0) {
        out.push_back(d); 
    }
    return out;
}

int main() {
    ll n;
    cin >> n;

    vector<ll> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    ll mx = *max_element(ns.begin(), ns.end());
    vector<ll> dp(mx + 1, 0);
    dp[0] = 1;
    for(ll k : ns) {
        for(ll d : divs(k)) {
            dp[d] = (dp[d] + dp[d - 1]) % MOD;
        }
    }

    ll total = 0;
    for(int i = 1; i <= mx; ++i) {
        total += dp[i];
        total %= MOD;
    }

    cout << total << endl;
}
