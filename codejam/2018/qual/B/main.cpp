#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void testcase() {
    ll n;
    cin >> n;

    vector<ll> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    vector<ll> ps;
    vector<ll> is;

    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) ps.push_back(ns[i]);
        else is.push_back(ns[i]);
    }

    sort(ps.begin(), ps.end());
    sort(is.begin(), is.end());

    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) ns[i] = ps[i / 2];
        else ns[i] = is[i / 2];
    }

    ll fl = -1;
    for(int i = 0; i < n - 1; ++i) {
        if(ns[i] > ns[i + 1]) {
            fl = i;
            break;
        }
    }

    if(fl == -1) cout << "OK" << endl;
    else cout << fl << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
