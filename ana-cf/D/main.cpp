#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, c;
    cin >> n >> c;

    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    int k = ns[0] - ns[1];
    for(int i = 1; i < n; ++i) k = max(k, ns[i - 1] - ns[i]);
    k -= c;
    cout << max(k, 0) << endl;
}
