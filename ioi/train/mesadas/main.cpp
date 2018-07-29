#include <bits/stdc++.h>
using namespace std;

int flog(int n) {
    return 8 * sizeof(int) - 1 - __builtin_clz(n);
}

vector<vector<int>> init(int n, int k) {
    n = 2 << flog(n);
    vector<vector<int>> st;
    while(n) {
        st.emplace_back(n, k);
        n /= 2;
    }

    return st;
} 

void update(int p, int k, vector<vector<int>> &st) {
    st[0][p] = k;
    p /= 2;
    for(int i = 1; i < st.size(); ++i) {
        st[i][p] = max(st[i-1][2*p], st[i - 1][2*p + 1]);
        p /= 2;
    }
}

int lo_bo(int k, vector<vector<int>> &st) {
    int p = 0;
    for(int i = st.size() - 1; i >= 1; --i) {
        if(st[i-1][2*p] >= k) p = 2*p;
        else p = 2*p + 1;
    }
    return p;
}

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
    auto st = init(n, 0);
    for(int i = 0; i < n; ++i) {
        s[i] = ns[i].second;
        update(i, s[i], st);
    }

    int stacks = 0;
    for(int i = 0; i < n; ++i) {
        update(i, -1, st);
        int lo = lo_bo(s[i], st);
        update(lo, -1, st);
        if(lo >= n) stacks++;
    }

    cout << stacks << endl;
}
