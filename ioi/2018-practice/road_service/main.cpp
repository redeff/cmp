#include <bits/stdc++.h>
using namespace std;
int INF = 333333;

int main() {
    int n, k, w;
    cin >> n >> k >> w;
    vector<vector<int>> tree(n);
    for(int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<int> depths(n, INF);
    function<void(int, int)> see = [&](int node, int depth) {
        if(depths[node] > depth) {
            depths[node] = depth;
            for(int ch : tree[node]) see(ch, depth + 1);
        }
    };

    see(0, 0);

    int ratio = n / k;
    int total = 0;
    for(int r = 0;total < k; ++r) {
        for(int i = 1; i < n && total < k; ++i) {
            if((depths[i]+r) % ratio == 0) {
                cout << 0 << " " << i << endl;
                total++;
            }
        }
    }

}
