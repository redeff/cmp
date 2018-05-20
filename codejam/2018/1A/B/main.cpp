#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void testcase() {
    ll r, b, c;
    cin >> r >> b >> c;

    vector<ll> ms(c), ns(c), ps(c);

    for(int i = 0; i < c; ++i) {
        cin >> ms[i] >> ns[i] >> ps[i];
    }

    ll lo = 0;
    ll hi = 4000000000000000000ll;

    while(hi - lo > 1) {
        ll mid = (hi + lo) / 2;

        vector<ll> bits(c);
        for(int i = 0; i < c; ++i) {
            bits[i] = max(min(ms[i], (mid - ps[i]) / ns[i]), 0ll);
        }

        sort(bits.begin(), bits.end());

        ll total = 0;
        for(int f = 0; f < r; ++f) {
            total += bits[c - 1 - f];
        }

        if(total < b) lo = mid;
        else hi = mid;
    }

    cout << hi << endl;

}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
