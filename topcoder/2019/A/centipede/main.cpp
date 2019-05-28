#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

class CentipedeSocks {
public:
    int fewestSocks(int c, int f, vector<int> socks) {
        ll total = 0;
        ll num_socks = 0;
        for(int i : socks) total += ll(i) / f;
        for(int i : socks) num_socks += ll(i);
        if(total < c) return -1;
        if(c == 0) return 0;

        vector<ll> mod;
        for(int i : socks) if(i >= f) mod.push_back(ll(i) % f + 1ll);
        sort(mod.begin(), mod.end());
        reverse(mod.begin(), mod.end());
        ll val = 0;
        while(total >= c) {
            total--;
            if(!mod.empty()) {
                val += mod.back();
                mod.pop_back();
            } else {
                val += f;
            }
        }

        return num_socks - val + 1ll;
    }
};
