#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> to(n, -1);
    for(int i = 1; i < n; ++i) {
        cin >> to[i];
        to[i]--;
    }

    vector<int> depth(n, -1);
    depth[0] = 0;

    function<int(int)> get_depth = [&](int node) {
        if(depth[node] != -1) return depth[node];
        int d = 1 + get_depth(to[node]);
        depth[node] = d;
        return d;
    };

    int total = 0;
    unordered_set<int> ds;
    for(int i = 0; i < n; ++i) {
        if(ds.count(get_depth(i)) == 1) {
            ds.erase(get_depth(i));
            total--;
        } else {
            ds.insert(get_depth(i));
            total++;
        }
        // ds.insert(get_depth(i));
    }

    cout << ds.size() << endl;
}
