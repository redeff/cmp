#include <bits/stdc++.h>
typedef long long int ll;

using namespace std;

int main() {
    ll n, u;
    cin >> n >> u;

    double rat = -1;

    vector<ll> ns(n);
    for(ll i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    ll lat = 0;
    for(ll i = 0; i < n; ++i) {
        while(lat < n && ns[lat] - ns[i] <= u) lat++;
        lat--;
        if(lat < i + 2) continue;
        ll mid = i + 1;
        rat = max(rat, double(double(ns[lat]) - double(ns[mid])) / double(double(ns[lat]) - double(ns[i])));
    }
    cout.precision(12);
    cout << rat << endl;
}
