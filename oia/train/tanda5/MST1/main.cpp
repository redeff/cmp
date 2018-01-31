#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector<ll> memo;
ll calc(ll t, bound) {
    if(bound == 0) return INF;
    if(memo[t] != -1) return memo[t];
    if(t == 1) return 0;
    ll ret = calc(t - 1, bound - 1) + 1;
    if(t % 2 == 0) ret = min(ret, calc(t / 2, bound - 1) + 1);
    if(t % 3 == 0) ret = min(ret, calc(t / 3, bound - 1) + 1);

    memo[t] = ret;
    return ret;
}

int main() {
    memo = vector<ll>(20000001, -1);
    ll t;
    cin >> t;
    for(ll i = 0; i < t; ++i) {
        ll n;
        cin >> n;
        cout << calc(n) << endl;
    }
}
