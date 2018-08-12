#include <bits/stdc++.h>
using namespace std;

struct Conn {
    int to;
    int id;
};

struct BiConn {
    int from;
    int to;
};

int main() {
    int t;
    cin >> t;
    for(int testcase = 0; testcase < t; ++testcase) {
        int n, m;
        cin >> n >> m;
        vector<BiConn> conns(m);
        vector<vector<Conn>> tree(n);
        vector<int> deg(n, 0);
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            conns[i] = {a, b};
            tree[a].push_back({b, i});
            tree[b].push_back({a, i});

            deg[a]++;
            deg[b]++;
        }

        vector<bool> used(m, false);
        vector<int> dir_deg(n, 0);

        function<void(int)> eq = [&](int node) {
            if(deg[node] % 2 != 0) return;
            if(dir_deg[node] == 0) return;

            // Nunca se vacía por cosas de paridad
            while(used[tree[node].back().id]) tree[node].pop_back();

            int id = tree[node].back().id;
            int to = tree[node].back().to;
            used[id] = true;

            if(dir_deg[node] == 1) {
                conns[id].from = node;
                conns[id].to = to;
            } else {
                conns[id].to = node;
                conns[id].from = to;
            }

            dir_deg[to] += dir_deg[node];
            dir_deg[node] = 0;

            eq(to);
        };

        for(int i = 0; i < conns.size(); ++i) {
            if(!used[i]) {
                used[i] = true;
                dir_deg[conns[i].from]--;
                dir_deg[conns[i].to]++;
                eq(conns[i].from);
                eq(conns[i].to);
            }
        }

        int even = 0;
        for(int i = 0; i < n; ++i) if(deg[i] % 2 == 0) even++;

        cout << even << endl;
        for(auto c : conns) {
            cout << c.from + 1 << " " << c.to + 1 << endl;
        }
    }
}
