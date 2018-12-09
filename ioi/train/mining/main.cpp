#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define mins(x, e) x = min(x, e)

pair<int, int> biconex(vector<vector<int>> &graph) {
    ll leaves = 0;
    ll ways = 1;
    int n = graph.size();

    vector<bool> seen(n, false);
    vector<int> depths(n, -1);

    vector<bool> block(n, false);

    function<int(int, int)> dfs1 = [&](int node, int depth) {
        seen[node] = true;
        depths[node] = depth;

        int children = 0;
        int min_reach = depth;
        for(int ch : graph[node]) {
            if(seen[ch]) {
                mins(min_reach, depths[ch]);
            } else {
                children++;
                int ret = dfs1(ch, depth + 1);
                if(ret == depth) block[node] = true;

                mins(min_reach, ret);
            }
        }

        if(children == 0) block[node] = false;
        if(depth == 0) block[node] = children > 1;

        return min_reach;
    };

    dfs1(0, 0);

    struct Ret2 {
        int deg;
        int size;
    };

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
                ways *= (ll) t.size;
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

        ll mx = 0;
        for(auto p : conns) mx = max((ll) max(p.first, p.second), mx);

        vector<vector<int>> graph(mx);
        for(auto p : conns) {
            p.first--;
            p.second--;
            graph[p.first].push_back(p.second);
            graph[p.second].push_back(p.first);
        }

        pair<ll, ll> p = biconex(graph);
        cout << "Case " << cas << ": ";
        if(p.second == 1 || p.second == 0) {
            cout << 2 << " " << (mx * (mx - 1)) / 2 << endl;
        } else {
            cout << p.second << " " << p.first << endl;
        }
    }
}
