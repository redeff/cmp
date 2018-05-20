#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k1, k2;
    cin >> n >> k1 >> k2;
    int k = k1 + k2;

    vector<int> ns(n);
    for(int i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    for(int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        ns[i] -= tmp;
        ns[i] = abs(ns[i]);
        // cerr << ns[i] << endl;
    }

    map<int, int> dp;
    for(int i = 0; i < n; ++i) {
        dp[ns[i]]++;
    }

    for(int i = 0; i < k; ++i) {
        dp.rbegin()->second--;
        int ix = dp.rbegin()->first;

        if(ix == 0) {
            dp[1]++;
        } else {
            dp[ix - 1]++;
        }

        if(dp[ix] == 0) dp.erase(ix);
    }

    long long int total = 0;
    for(auto p : dp) {
        // cerr << p.first << ":" << p.second << endl;
        total += (long long int) p.first * (long long int) p.first * (long long int) p.second;
    }

    cout << total << endl;
}
