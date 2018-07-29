#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef YO
    freopen("mesadas.in", "r", stdin);
    freopen("mesadas.out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<pair<int, int>> ns(n);
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if(a < b) swap(a, b);
        ns[i] = {a, b};
    }

    sort(ns.begin(), ns.end());

    vector<int> s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = -ns[i].second;
    }

    vector<int> stacks;
    for(int i = 0; i < n; ++i) {
        auto lo = lower_bound(stacks.begin(), stacks.end(), s[i]);
        if(lo == stacks.end()) stacks.push_back(s[i]);
        else *lo = s[i];
    }

    cout << stacks.size() << endl;
}
