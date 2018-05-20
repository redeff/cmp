#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 1e9 + 7;

ll ex(ll b, ll e) {
    if(e == 0) return 1;
    ll rec = ex(b, e/2);

    if(e % 2 == 0) {
        return (rec * rec) % MOD;
    } else {
        return (((rec * rec) % MOD) * b) % MOD;
    }
}

ll inv(ll n) {
    return ex(n, MOD - 2);
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<int> as(n);
    vector<int> bs(n);

    for(int i = 0; i < n; ++i) {
        cin >> as[i];
    }

    for(int i = 0; i < n; ++i) {
        cin >> bs[i];
    }

    int t = n;
    for(int i = 0; i < n; ++i) {
        if(as[i] != 0 && bs[i] != 0) {
            t = i;
            break;
        }
    }

    ll inv_m = inv(m);
    ll inv_2 = inv(2);

    ll curr = t == n ? 0 : (as[t] > bs[t] ? 1 : 0);

    for(int i = t - 1; i >= 0; --i) {
        curr *= inv_m;
        curr = curr % MOD;

        if(as[i] == 0 && bs[i] == 0) {
            curr += (((inv_2 * inv_m) % MOD) * (m - 1)) % MOD;
        } else if(as[i] == 0) {
            curr += inv_m * (m - bs[i]) % MOD;
        } else {
            curr += inv_m * (as[i] - 1) % MOD;
        }
        curr = curr % MOD;
    }

    curr = (curr + MOD) % MOD;

    cout << curr << endl;
}
