#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

pair<ll, ll> calc(ll n, ll m, ll k) {
    if(k < n) {
        return {k, 0};
    }
     else k -= n;
     m -= 1;

     ll h = k / (2 * m);
     ll p = k % (2 * m);

     if(p < m) return {n - 1 - 2 * h, 1 + p};
     else return {n - 1 - 2 * h - 1, 2 * m - p};
}

int main() {
    ll n, m, k;
    cin >> n >> m >> k;

    auto res = calc(n, m, k);
    cout << res.first + 1 << " " << res.second + 1 << endl;

}
