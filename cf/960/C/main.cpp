#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    ll x, d;
    cin >> x >> d;

    vector<ll> total;
    for(ll i = 0; (x >> i) > 0; ++i) {
        if((1 << i) & x) {
            for(ll j = 0; j < i; ++j) total.push_back((2 * d + 2) * i);
            total.push_back((2 * d + 2) * i + d + 1);
        }
    }

    cout << total.size() << endl;
    for(auto k : total) cout << k << " ";
    cout << endl;
}
