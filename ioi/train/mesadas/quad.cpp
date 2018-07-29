#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
    auto st = init(15, 0);
    update(5, 100, st);
    // update(6, 1000, st);
    update(5, 99, st);
    update(4, 99, st);
    cout << lo_bo(100, st) << endl;
    */

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
        s[i] = ns[i].second;
    }

    vector<bool> used(n, false);

    int stacks = 0;
    for(int i = 0; i < n; ++i) {
        used[i] = true;
        int lo = -1;
        for(int j = 0; j < n; ++j) if(!used[j]) if(s[j] >= s[i]) {
            lo = j;
            break;
        }
        if(lo == -1) stacks++;
        else used[lo] = true;
    }

    cout << stacks << endl;
}
