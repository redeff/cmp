#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

pair<ll, int> biconex(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> depths(n, 0);
    
    vector<bool> seen(n, false);
    struct Ret {
        int mn;
        int size;
        bool has_leaf;
        int num_comp;
        int comp_size;
    };

    ll ways = 1;
    int leafs = 0;

    function<Ret(int, int)> see = [&](int node, int depth) {
        seen[node] = true;
        depths[node] = depth;

        Ret out;
        out.has_leaf = false;
        out.mn = n;
        out.size = 1;
        out.num_comp = 0;

        bool leaf = true;
        for(int ch : graph[node]) {
            if(!seen[ch]) {
                leaf = false;
                Ret ret = see(ch, depth + 1);
                if(ret.has_leaf) out.has_leaf = true;
                out.mn = min(out.mn, ret.mn);
                out.size += ret.size;
                out.num_comp += ret.num_comp;
                out.comp_size = ret.comp_size;
            }
            else {
                out.mn = min(out.mn, depths[ch]);
            }
        }

        out.has_leaf |= leaf;

        if(out.mn == depth - 1 && out.has_leaf && depth != 0) { // node parte componentes biconexas
            leafs++;
            ways *= (ll) out.size;
            out.has_leaf = false;
        }

        if(out.mn == depth - 1) {
            out.num_comp = 1;
            out.comp_size = out.size;
        }

        return out;
    };

    Ret r = see(0, 0);
    if(r.num_comp == 1) {
        ways *= n - r.comp_size;
        leafs++;
    }

    return {ways, leafs};
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
        if(p.second == 1) {
            cout << 2 << " " << (mx * (mx - 1)) / 2 << endl;
        } else {
            cout << p.second << " " << p.first << endl;
        }
    }
}
