#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    vector<ll> ns(14);
    for(int i = 0; i < 14; ++i) {
        cin >> ns[i];
    }

    ll mx = -1;
    for(int i = 0; i < 14; ++i) {
        vector<ll> ms(ns);

        for(int j = 0; j < ns[i]; ++j) {
            ms[(j + i + 1) % 14]++;
        } 

        ll total = 0;
        for(int j = 0; j < 14; ++j) {
            total += ms[j] * (1 - ms[j] % 2);
        }

        mx = max(mx, total);
    }

    cout << mx << endl;
}
