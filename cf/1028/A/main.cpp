#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    ll n, m;
    cin >> n >> m;
    ll x = 0;
    ll y = 0;
    ll total = 0;
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for(int j = 0; j < m; ++j) {
            if(s[j] == 'B') {
                x += i;
                y += j;
                total++;
            }
        }
    }

    cout << 1 + x/total << " " << 1 + y/total << endl;

}
