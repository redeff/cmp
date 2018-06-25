#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 1e9 + 7;

ll f(ll median, ll i, ll a, ll b, ll c) {
    ll ret = (a * median) % MOD;
    ret += (i * b) % MOD;
    ret %= MOD;
    ret += c;
    ret %= MOD;
    return ret;
}

void testcase() {
    ll a, b, c, n;
    cin >> a >> b >> c >> n;

    priority_queue<ll> lo;
    lo.push(1ll);
    priority_queue<ll> hi;

    auto add = [&](ll k) {
        if(k > lo.top()) hi.push(-k);
        else             lo.push(k);

        if(lo.size() - 1 > hi.size()) {
            ll t = lo.top();
            lo.pop();
            hi.push(-t);
        } else if(lo.size() < hi.size()) {
            ll t = hi.top();
            hi.pop();
            lo.push(-t);
        }
    };

    ll total = 1;

    for(ll i = 1; i < n; ++i) {
        ll median = lo.top();
        ll val = f(median, i+1, a, b, c);
        add(val);
        total += val;
    }

    cout << total << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) testcase();
}
