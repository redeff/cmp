#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_set<int> xs;
    unordered_set<int> ys;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xs.insert(x);
        ys.insert(y);
    }

    cout << min(xs.size(), ys.size()) << endl;
}
