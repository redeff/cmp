#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll from(ll num, ll pos) {
    return (num >> pos) % (1ll << 7ll);
}

int main() {
    ll t, w;
    cin >> t >> w;
    for(int test = 0; test < t; ++test) {
        ll lo, hi;
        ll a, b;
        a = 56;
        b = 227;
        cout << a << endl << flush;
        cin >> lo;
        cout << b << endl << flush;
        cin >> hi;

        ll nums[7];
        nums[1] = from(lo, a/1ll);
        nums[2] = from(lo, a/2ll);
        nums[4] = from(hi, b/4ll);
        nums[5] = from(hi, b/5ll);
        nums[6] = from(hi, b/6ll);
        for(ll i = 1; i <= 6; ++i) if(i != 3) lo -= (nums[i] << (a/i));
        nums[3] = from(lo, a/3);
        cout <<
            nums[1] << " " <<
            nums[2] << " " <<
            nums[3] << " " <<
            nums[4] << " " <<
            nums[5] << " " <<
            nums[6] << endl;
        int dummy;
        cin >> dummy;
        if(dummy == -1) exit(-1);
        /*
        cerr <<
            nums[1] << " " <<
            nums[2] << " " <<
            nums[3] << " " <<
            nums[4] << " " <<
            nums[5] << " " <<
            nums[6] << endl;
        */
    }
}
