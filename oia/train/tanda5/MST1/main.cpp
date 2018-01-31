#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll calc(ll t) {
    if(t == 1) return 0;
    if(t == 2) return 1;
    return min(calc(t / 2) + t % 2 + 1, calc(t / 3) + t % 3 + 1);
}

int main() {
    ll t;
    cin >> t;
    for(ll i = 0; i < t; ++i) {
        ll n;
        cin >> n;
        cout << "Case " << i + 1 << ": " << calc(n) << endl;
    }
}
