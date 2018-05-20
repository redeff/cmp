#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> ns(n);
    for(int i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    for(int i = 0; i < n; ++i) {
        sort(ns[i].begin(), ns[i].end());
        auto it = unique(ns[i].begin(), ns[i].end());
        ns[i].resize(distance(ns[i].begin(), it));
    }

    sort(ns.begin(), ns.end());
    auto it = unique(ns.begin(), ns.end());
    ns.resize(distance(ns.begin(), it));

    cout << ns.size();
}
