#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void testcase() {
    ll a;
    cin >> a;
    
    vector<vector<bool>> empt = {{false, false, false}, {false, false, false}, {false, false, false}};
    vector<vector<bool>> full = {{true, true, true}, {true, true, true}, {true, true, true}};
    vector<vector<bool>> curr = empt;
    ll ix = 2;
    while(true) {
        if(curr == full) {
            ix += 3;
            curr = empt;
        } else {
            cout << ix << " " << 5 << endl << flush;
            ll x, y;
            cin >> x >> y;
            if(x == 0 && y == 0) return;
            curr[ix - x + 1][5 - y + 1] = true;
        } 
    }
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        // cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
