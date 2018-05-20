#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll log2(ll n) {
    ll i = 0;
    ll pw = 1;
    while(pw <= n) {i++; pw = pw << 1;}
    return i - 1;
}

ll mod(ll x, ll m) {
    return ((x % m) + m) % m;
}

int main() {
    ll q;
    cin >> q;

    // 62 > log2 10^18
    vector<ll> cyc(62, 0);

    for(ll i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if(t == 1) {
            ll x, k;
            cin >> x >> k;
            ll dep = log2(x);
            ll pw =  1ll << dep;
            cyc[dep] = mod(cyc[dep] - k, pw);
            cyc[dep + 1] = mod(cyc[dep + 1] + 2 * k, pw << 1);
        } else if(t == 2) {
            ll x, k;
            cin >> x >> k;

            ll dep = log2(x);
            ll pw = 1ll << dep;
            cyc[dep] = mod(cyc[dep] - k, pw);

            /*
            while(dep < 61) {
                // cerr << "R" << endl;
                cyc[dep] = mod(cyc[dep] - k, (1ll << dep));
                dep += 1ll;

                k *= 2ll;
            }
            */
        } else if(t == 3) {
            ll x;
            cin >> x;

            ll dep = log2(x);
            // ll pos = x - (1ll << dep) - cyc[dep];
            ll pw = 1ll << dep;
            ll pos = mod(x - cyc[dep], pw);
            // cerr << "R\n" << endl;

            ll cy = 0;
            for(ll j = 0, pw = 1; j <=dep; ++j, pw = pw << 1ll) {
                cy = mod(cy * 2 + cyc[j], pw);
            }

            while(dep >= 0) {
                // cerr << "U" << endl;
            // cerr << "U\n" << endl;
            // cout << "U ";
                //cout << (1ll << dep) + (pos + cyc[dep] + (1ll << dep)) % (1 << dep) << " ";
                cout << pw + mod(pos + cy, pw) << " ";

                if(dep != 0)
                    cy = mod((cy - cyc[dep]) / 2, pw / 2);

                dep--;
                pw = pw >> 1ll;
                pos = pos >> 1ll;
            }
            cout << endl << flush;
        }
    }
}
