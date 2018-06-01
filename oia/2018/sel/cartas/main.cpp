#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll k;
ll km;

ll expand(ll d, ll t) {
    // cerr << t << endl;
    ll r = k * (t / km) + t % km + 1;
    return r - max(0ll, r / k - d + 1);
}

ll augment(ll n, ll d, ll r) {
    if(n == 1) return 0;
    if(n - d <= 0) {
        exit(1);
    }

    ll last = d * k;
    ll trans = last + r;
    if(trans < n) return trans;
    trans -= n;
    trans %= n - d;
    return expand(d, trans);
}


ll solve(ll n) {
    ll p = 1;
    ll r = 0;
    while(p < n) {
        ll d = min((p + km) / km, n - p);
        // cerr << "p " << p << "; r " << r << "; d " << d << endl;
        p += d;
        r = augment(p, d, r);
    }

    return r;
}

int solitario(vector<int> c, long long N, int K) {
    if(c.empty()) return -1;
    k = K + 1;
    km = K;
    ll r = solve(N) % N;
    r = N - 1 - r;
    r %= (ll) c.size();
    r += (ll) c.size();
    r %= (ll) c.size();
    return c[r];
}
