#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> ns(n, -1);
    for(int j = 0; j < m; ++j) {
        int b;
        cin >> b;
        b--;
        for(int i = b; i < n && ns[i] == -1; ++i) {
            ns[i] = b;
        }
    }

    for(int k: ns) cout << k+1 << " ";
    cout << endl;
}
