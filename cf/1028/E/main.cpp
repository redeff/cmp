#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    int index = -1;
    for(int i = 0; i < n; ++i) {
        if(ns[i] < ns[(i+1) % n]) index = i;
    }

    if(index == -1) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> out(n);
    {
        out[(index + 1) % n] = ns[(index + 1) % n]; 
        for(int i = index; i != (index + 1) % n; i = (i + n - 1) % n) {
            int nxt = (i + 1) % n;
            int prv = (i + n - 1) % n;
            out[i] = ns[i] + ((ns[prv] - ns[i]) / out[nxt] + 1) * out[nxt];
        }
    }

    cout << "YES" << endl;
    for(int o : out) cout << o << " ";
    cout << endl;
}
