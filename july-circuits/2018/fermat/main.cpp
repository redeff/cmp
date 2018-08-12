#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Divisor {
    ll p;
    int a;
};

vector<Divisor> factor(ll n) {
    // assert(n != 0);
    vector<Divisor> ds;
    for(ll i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            ds.push_back({i, 0});
            while(n % i == 0) {
                ds.back().a++;
                n /= i;
            }
        }
    }

    if(n != 1) {
        ds.push_back({n, 1});
    }

    return ds;
};

ll gcd(ll a, ll b) {
    if(a < b) swap(a, b);
    while(b != 0) {
        a = a % b;
        swap(a, b);
    }

    return a;
}

vector<Divisor> factor_divisor(ll n, vector<Divisor> &ds) {
    // assert(n != 0);
    auto my = ds;
    for(int i = 0; i < my.size(); ++i) {
        my[i].a = 0;
        int pa = 1;
        while(n % pa == 0) {
            pa *= my[i].p;
            my[i].a++;
        }
        my[i].a--;
        my[i].a = min(my[i].a, ds[i].a);
    }
    return my;
}

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

ll proot(ll p, vector<Divisor> &ds) {
    for(ll r = 2; r < p; ++r) {
        bool god = true;
        for(auto d : ds) {
            if(mod_exp(r, (p-1) / d.p, p) == 1) god = false;
        } 
        if(god) return r;
    }
}

int main() {
    ll p;
    ll l;
    cin >> p >> l;

    auto ds = factor(p - 1);
    ll root = proot(p, ds);

    vector<int> val(p);
    {
        ll r = root;
        for(int i = 1; i < p; ++i) {
            val[r] = i;
            r *= root;
            r %= p;
        }
    }

    /*
    for(int i = 0; i < val.size(); ++i) {
        cout << i << " " << val[i] << endl;
    }
    // for(int v : val) cout << v << " ";
    cout << endl;
    */

    vector<ll> cum_prod;
    cum_prod.push_back(1);
    for(auto d : ds) {
        cum_prod.push_back(cum_prod.back() * (ll) (d.a + 1));
    }
    vector<bool> divisor_space(cum_prod[ds.size()], false);

    for(int a = 2; a < p; ++a) {
        // a + b = 1
        // b = 1 - a
        ll b = (1 - a + p) % p;

        ll d = gcd(val[a], val[b]);
        auto fact = factor_divisor(d, ds);

        ll index = 0;
        for(int i = 0; i < ds.size(); ++i) {
            index += cum_prod[i] * fact[i].a;
        }

        divisor_space[index] = true;
    }

    for(int index = p - 1; index >= 1; index--) if((p - 1) % index == 0) {
        auto fact = factor_divisor(index, ds);
        ll ix = 0;
        for(int i = 0; i < ds.size(); ++i) {
            ix += fact[i].a * cum_prod[i];
        }
        for(int i = 0; i < ds.size(); ++i) if(fact[i].a < ds[i].a) {
            ll ni = ix + cum_prod[i];
            divisor_space[ix] = divisor_space[ix] || divisor_space[ni];
        }
    }
    /*
    for(int index = cum_prod.back() - 1; index >= 0; --index) {
        auto fact = factor_divisor(index, ds);

        for(int i = 0; i < ds.size(); ++i) if(fact[i].a < ds[i].a) {

        }
        for(int i = 0; i < ds.size(); ++i) {
            if(index + cum_prod[i] < cum_prod.back()) {
                divisor_space[index] = divisor_space[index] || divisor_space[index + cum_prod[i]];
                // cerr << index << " + " << cum_prod[i] << endl;
            } else {
                // cerr << index << " + " << cum_prod[i] << endl;
            }
        }

        // cout << divisor_space[index] << " ";
    }
    */

    ll total = 0;
    ll les = 0;
    for(ll k = 1; k < p; ++k) {
        ll d = gcd(k, p - 1);
        auto fact = factor_divisor(d, ds);

        ll index = 0;
        for(int i = 0; i < ds.size(); ++i) {
            index += cum_prod[i] * fact[i].a;
        }

        // cout << index << " ";

        if(divisor_space[index]) {
            total++;
            if(k <= l % (p - 1)) les++;
        }
    }

    cout << les + total * (l / (p - 1)) << endl;
    /*
    for(ll k = 1; k <= l; ++k) {
        ll d = gcd(k, p - 1);
        auto fact = factor_divisor(d, ds);

        ll index = 0;
        for(int i = 0; i < ds.size(); ++i) {
            index += cum_prod[i] * fact[i].a;
        }

        // cout << index << " ";

        if(divisor_space[index]) {
            cout << k << " ";
        }
    }
    cout << endl;
    */
 
}
