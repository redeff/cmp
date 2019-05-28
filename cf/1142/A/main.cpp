#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll gcd(ll a, ll b) {
    if(a < 0ll) a = -a;
    if(b < 0ll) b = -b;
    if(a < b) swap(a, b);
    while(b != 0ll) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ll n, k;
    cin >> n >> k;

    ll a, b;
    cin >> a >> b;

    vector<ll> ds = {a + b, a - b};
    ll x = n * k;
    ll y = 0ll;
    for(ll i : ds) {
        for(ll j = -1ll; j <= 2*n+100; ++j) {
            x = min(x, n*k/gcd(n*k, k*j+i));
            y = max(y, n*k/gcd(n*k, k*j+i));
        }
    }
    cout << x << " " << y << endl;
}
