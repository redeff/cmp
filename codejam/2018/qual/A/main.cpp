#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll pw2(ll i) {
    if(i == 0) return 1;
    else return 2ll * pw2(i - 1);
}

void testcase() {
    ll d;
    cin >> d;
    string s;
    cin >> s;

    vector<ll> vals {0};

    for(char c : s) {
        if(c == 'C') vals.push_back(0);
        else vals.back()++;
    }

    ll ix = vals.size() - 1;
    ll sum = 0;
    ll op = 0;

    for(ll i = 0; i < vals.size(); ++i) {
        sum += pw2(i) * vals[i];
    }

    // cerr << vals.size() << endl;
    // cerr << sum << endl;
    // cerr << d << endl;
    while(sum > d && ix > 0) {
        // cerr << ix << endl;
        if(vals[ix] == 0) ix--;
        else {
            op++;
            vals[ix]--;
            vals[ix - 1]++;
            sum -= pw2(ix - 1); 
        }
    }

    if(sum > d) cout << "IMPOSSIBLE" << endl;
    else cout << op << endl; 

}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
