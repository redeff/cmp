#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    int n;
    cin >> n;
    
    vector<ll> ns(n, 0);
    for(int i = 0; i < n/2; ++i) {
        cin >> ns[i];
    }

    for(int i = 0; i < n/2; ++i) {
        int other = n - i - 1;
        if(i == 0) {
            ns[other] = ns[i];
            ns[i] = 0;
        } else {
            ll total = ns[i];
            ns[other] = min(ns[other + 1], ns[i]);
            ns[i] = total - ns[other];

            ns[i] = max(ns[i], ns[i - 1]);
            ns[other] = total - ns[i];
        }
    }

    for(ll t : ns) cout << t << " ";
    cout << endl;
}
