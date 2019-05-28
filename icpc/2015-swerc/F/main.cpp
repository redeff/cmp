#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m && n != 0) {

        vector<int> tree(n, 0);
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            tree[a] |= 1 << b;
            tree[b] |= 1 << a;
        }

        if(m != n-1) {
            cout << "Impossible" << endl;
            continue;
        }

        function<int(int)> expand = [&] (int state) {
            int nstate = 0;
            for(int j = 0; j < n; ++j) {
                if(state & tree[j]) nstate |= 1 << j;
            }
            return nstate;
        };
        int inf = 333333;
        int last = 1 << n;
        last--;

        vector<int> len(1 << n, inf);
        len[0] = 0;
        function<void(int)> dfs = [&](int state) {
            if(state == 0) return;
            if(len[state] < inf) return;
            len[state] = min(len[state], inf - 1);
            for(int i = 0; i < n; ++i) {
                int e = expand(state & ~(1 << i));
                dfs(e);
                len[state] = min(len[state], len[e] + 1);
            }
        };

        function<void(int)> dfs2 = [&] (int state) {
            for(int i = 0; i < n; ++i) {
                int e = expand(state & ~(1 << i));
                if(len[e] + 1 == len[state]) {
                    cout << i << " ";
                }
                dfs2(e);
                return;
            }
        };

        dfs(last);
        dfs2(last);
    }
}
