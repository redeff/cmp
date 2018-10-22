#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    int t;
    cin >> t;
    for(int sdf = 0; sdf < t; ++sdf) {
        int n;
        cin >> n;
        vector<int> ns(n);
        for(int i = 0; i < n; ++i) cin >> ns[i];

        unordered_set<int> diffs;
        for(int i = 0; i < n; ++i) if(ns[i] != -1) diffs.insert(ns[i] - i);

        int i = 0;

        if(diffs.size() < 2) {
            cout << "inf" << endl;
        } else {
            int i = *diffs.begin();
            int g = 0;
            for(int d : diffs) g = gcd(abs(i - d), g);
            if(g < *max_element(ns.begin(), ns.end())) {
                cout << "impossible" << endl;
            } else {
                cout << g << endl;
            }
        }
    }
}
