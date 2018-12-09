#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 1000000007;

struct Show {
    ll beg;
    ll end;
};

int main() {
    ll n, x, y;
    cin >> n >> x >> y;
    x -= y;

    vector<Show> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i].beg >> ns[i].end;

    sort(ns.begin(), ns.end(), [&](Show a, Show b) {return a.beg < b.beg;});
    ll total = 0;
    multiset<ll> finish_times;
    for(Show s : ns) {
        auto it = finish_times.lower_bound(s.beg);
        if(it == finish_times.begin()) {
            total += x;    
        } else {
            it--;
            ll last = *it;
            finish_times.erase(it);

            ll gap = s.beg - last - 1;
            gap %= MOD;
            total += min(gap * y, x) % MOD;
            total %= MOD;
        }

        finish_times.insert(s.end);
        total += y * ((s.end - s.beg + 1) % MOD) % MOD;
        total %= MOD;
    }

    cout << total << endl;
}
