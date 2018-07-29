#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll mod_exp(ll b, ll e, ll mod) {
    if(e == 0) return 1;
    else {
        ll rec = mod_exp(b, e/2, mod);
        rec = (rec * rec) % mod;
        if(e % 2 != 0) {
            rec *= b;
            rec %= mod;
        }
        return rec;
    }
}

bool is_kth_root(ll n, ll k, ll p) {
    for(ll i = 0; i < p; ++i) {
        if(mod_exp(i, k, p) == n) return true;
    }

    return false;
}

int main() {
    ll p;
    ll l;
    cin >> p >> l;
    int total = 0;
    int les = 0;
    /*
    for(int k = 1; k <= p - 1; ++k) {
        bool possible = false;
        for(int a = 2; a < p; ++a) {
            if(is_kth_root(a, k, p) && is_kth_root((1 - a + p) % p, k, p)) possible = true;
        }
        if(possible) {
            total++;
            if(k <= l % (p - 1)) les++;
        }
    }
    cout << les + total * (l / (p - 1)) << endl;
    */
    for(int k = 1; k <= l; ++k) {
        bool possible = false;
        for(int a = 2; a < p; ++a) {
            if(is_kth_root(a, k, p) && is_kth_root((1 - a + p) % p, k, p)) possible = true;
        }
        if(possible) {
            cout << k << " ";
        }
    }
    cout << endl;
}
