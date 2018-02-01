#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];
    unordered_set<int> dp;
    vector<int> ans(n);

    // Vamos guardando en un set los numeros que ya vimos,
    // y luego en and los tamaños de esos sets
    for(int i = n - 1; i >= 0; --i) {
        dp.insert(ns[i]);
        ans[i] = dp.size();
    }

    for(int i = 0; i < m; ++i) {
        int l;
        cin >> l;
        cout << ans[l - 1] << endl;
    }
}
