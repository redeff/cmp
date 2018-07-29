#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    while(!ns.empty() && ns.back() <= k) ns.pop_back();
    reverse(ns.begin(), ns.end());
    while(!ns.empty() && ns.back() <= k) ns.pop_back();

    cout << n - ns.size() << endl;
}
