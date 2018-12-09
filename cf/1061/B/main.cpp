#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];
    sort(ns.begin(), ns.end());
    ll h = 1;
    for(int i = 1; i < n; ++i) {
        if(h < ns[i]) ++h;
    }



    cout << accumulate(ns.begin(), ns.end(), 0ll) - (n + ns.back() - h) << endl;
    /*

    ll a = *max_element(ns.begin(), ns.end());
    ll t = accumulate(ns.begin(), ns.end(), 0ll);
    cout << (t - max(a, n)) << endl;
    */
}
