#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define mins(x, e) x = min(x, e)

pair<int, int> biconex(vector<vector<int>> &graph) {
    int n = graph.size();
    ll ways = 1;
    ll leaves = 0;

    vector<bool> block(n, false);
    for(int i = 0; i < n; ++i) {
        vector<bool> seen(n, false);
        seen[i] = true;

        function<void(int)> dfs = [&](int node) {
            if(seen[node]) return;
            seen[node] = true;
            for(int ch : graph[node]) dfs(ch);
        };

        if(i != 0) dfs(0);
        else dfs(1);

        for(bool b : seen) if(b == false) block[i] = true;
    }

    struct Ret2 {
        int deg;
        int size;
    };

    vector<bool> seen(n, false);
    seen = block;
    function<Ret2(int)> dfs2 = [&](int node) {
        seen[node] = true;

        Ret2 out;
        out.deg = 0;
        out.size = 1;
        for(int ch : graph[node]) if(!seen[ch]) {
            if(block[ch]) out.deg++;
            else if(!seen[ch]) {
                Ret2 t = dfs2(ch);
                out.deg += t.deg;
                out.size += t.size;
            }
        }

        return out;
    };

    for(int i = 0; i < n; ++i) if(!block[i]) {
        if(!seen[i]) {
            Ret2 t = dfs2(i);
            if(t.deg == 0 || t.deg == 1) {
                leaves++;
                ways *= t.size;
            }
        }
    }

    return {ways, leaves};
}

int main() {
    int cas = 0;
    while(true) {
        cas++;
        int n;
        cin >> n;
        if(n == 0) break;
        vector<pair<int, int>> conns(n);
        for(int i = 0; i < n; ++i) cin >> conns[i].first >> conns[i].second;

        int mx = 0;
        for(auto p : conns) mx = max(max(p.first, p.second), mx);

        vector<vector<int>> graph(mx);
        for(auto p : conns) {
            p.first--;
            p.second--;
            graph[p.first].push_back(p.second);
            graph[p.second].push_back(p.first);
        }

        pair<ll, int> p = biconex(graph);
        cout << "Case " << cas << ": ";
        if(p.second == 1 || p.second == 0) {
            cout << 2 << " " << (mx * (mx - 1)) / 2 << endl;
        } else {
            cout << p.second << " " << p.first << endl;
        }
    }
}
