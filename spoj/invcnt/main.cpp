#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 333333333333333;

vector<ll> merge_count(ll* ns, ll n, ll &total) {
    if(n < 2) {
        vector<ll> s(n);
        for(ll i = 0; i < n; ++i) s[i] = ns[i];
        return s;
    }
    auto as = merge_count(ns, n/2, total);
    auto bs = merge_count(ns + n/2, n - n/2, total);
    vector<ll> ret;
    ll a = 0;
    ll b = 0;
    for(ll i = 0; i < n; ++i) {
        ll av = a < as.size() ? as[a] : INF;
        ll bv = b < bs.size() ? bs[b] : INF;
        if(av <= bv) {
            ret.push_back(av);
            a++;
            total += b;
        } else {
            ret.push_back(bv);
            b++;
            // total += as.size() - a;
        }
    }
    return ret;
}

int main() {
    ll t;
    cin >> t;
    for(ll test = 0; test < t; ++test) {
        ll n;
        cin >> n;
        vector<ll> ns(n);
        for(ll &i : ns) cin >> i;
        ll total = 0;
        vector<ll> res = merge_count(&ns[0], n, total);
        cout << total << endl;
    }
}