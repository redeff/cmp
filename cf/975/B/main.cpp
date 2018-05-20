#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    vector<ll> ns(14);
    for(int i = 0; i < 14; ++i) {
        cin >> ns[i];
    }

    ll mx = -1;
    for(int i = 0; i < 14; ++i) {
        ll rocks = ns[i];
        if(rocks != 0) {

            vector<ll> ms(14);
            for(int j = 0; j < 14; ++j) {
                ms[j] = ns[j];
            }
            ms[i] = 0;

            ll cyc = rocks / 14;
            for(int j = 0; j < 14; ++j) {
                ms[j] += cyc;
            }
            for(int j = 0; j < (rocks % 14ll); ++j) {
                ms[(j + i + 1) % 14]++;
            } 

            ll total = 0;
            for(int j = 0; j < 14; ++j) {
                if(ms[j] % 2 == 0) {
                    total += ms[j];
                }
            }

            mx = max(mx, total);
        }
    }

    cout << mx << endl;
}
