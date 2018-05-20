#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll doit(ll n, ll k) {
    map<ll, ll> dp;
    dp[n] = 1;

    while(true) {
        ll ix = dp.rbegin()->first;
        ll val = dp.rbegin()->second;
        if(val < k) {
            dp[ix / 2] += val;
            dp[(ix + 1) / 2] += val;
            dp.erase(ix);
            k -= val;
        } else {
            return ix;
        }
    }
}

void testcase() {
    ll n, k;
    cin >> n >> k; 
    n++;

    ll res = doit(n, k);
    cout << (res + 1) / 2 - 1 << " " << res / 2 - 1 << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
