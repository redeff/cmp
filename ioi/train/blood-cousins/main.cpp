#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> ch;
    int dad;
    int depth;
    int lo;
    int hi;
};

int main() {
    int n;
    cin >> n;

    vector<Node> ns(n + 1);

    int root = 0;
    for(int i = 1; i <= n; ++i) {
        int dad;
        cin >> dad;
        ns[i].dad = dad;
        ns[dad].ch.push_back(i);
    }
    // ns[root].dad = root;


    function<int(int, int, int)> calc = [&](int node, int depth, int lo) {
        ns[node].depth = depth;
        ns[node].lo = lo;
        int hi = lo;
        for(int ch : ns[node].ch) {
            hi += calc(ch, depth + 1, hi);
        }
        if(ns[node].ch.empty()) hi++;
        ns[node].hi = hi;
        return hi - lo; // Cantidad de hojas
    };

    calc(root, 0, 0);

    vector<vector<int>> levels(n + 1);
    for(int i = 0; i <= n; ++i) {
        levels[ns[i].depth].push_back(i);
    }

    for(int i = 0; i <= n; ++i) {
        sort(levels[i].begin(), levels[i].end(), [&](int a, int b) {return ns[a].hi < ns[b].hi;});
    }

    // --------------

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int v, p;
        cin >> v >> p;

        int depth_pdad = ns[v].depth - p;
        if(depth_pdad <= 0) {
            cout << 0 << " ";
        } else {
            int node = *lower_bound(
                    levels[depth_pdad].begin(),
                    levels[depth_pdad].end(),
                    v,
                    [&](int a, int b){
                        return ns[a].hi < ns[b].hi;
                    });
            auto beg = levels[ns[v].depth].begin();
            auto end = levels[ns[v].depth].end();
            auto lo = lower_bound(beg, end, node, [&](int a, int b) {return ns[a].lo < ns[b].lo;});
            auto hi = upper_bound(beg, end, node, [&](int a, int b) {return ns[a].hi < ns[b].hi;});
            cout << hi - lo - 1 << " ";
        }
    }
    cout << endl;
}
