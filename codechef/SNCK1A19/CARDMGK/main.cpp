#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    ll t;
    cin >> t;
    for(ll sdf = 0; sdf < t; ++sdf) {
        ll n;
        cin >> n;
        vector<ll> ns(n);
        for(int i = 0; i < n; ++i) cin >> ns[i];

        ll neg = 0;
        for(ll i = 1; i < n; ++i) {
            if(ns[i] < ns[i - 1]) neg++;
        }

        if(ns.back() > ns.front()) neg++;

        if(neg > 1) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
}
