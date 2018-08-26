#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll MOD = 1'000'000'007;

int bounded_dfs(int bound, int node, int from, vector<unordered_set<int>> &tree) {
    if(bound <= 1) return bound;
    int size = 1;
    for(auto ch : tree[node]) {
        if(ch != from) {
            size += bounded_dfs(bound - size, ch, node, tree);
        }
    }

    return size;
}

int smallest(int u, int v, vector<unordered_set<int>> &tree) {
    tree[u].erase(v);
    tree[v].erase(u);
    for(int k = 1; true; k *= 2) {
        if(k > bounded_dfs(k, u, -1, tree)) return u;
        if(k > bounded_dfs(k, v, -1, tree)) return v;
    }
}

struct Island {
    ll anger;
    int part;
};

struct Part {
    ll anger;
    int count;
    ll mult;
};

int main() {
    int n;
    cin >> n;
    vector<Island> ns(n);
    vector<Part> ps {{0, n, 1}};
    for(int i = 0; i < n; ++i) {
        cin >> ns[i].anger;
        ns[i].part = 0;
        ps[0].anger += ns[i].anger;
    }

    vector<unordered_set<int>> tree(n);
    for(int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        tree[u].insert(v);
        tree[v].insert(u);
    }

    ll total = ps[0].anger;
    for(int q = 0; q < n-1; ++q) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        if(q != 0) {
            u += total;
            v += total;
        }

        ll a = smallest(u, v, tree);
        ll b = u + v - a;

        total -= ps[ns[b].part].mult * ps[ns[b].part].anger % MOD;

        ps.push_back({0, 0, 1});
        function<void(int, int)> see = [&](int node, int from) {
            ps.back().count++;
            ps.back().anger += ns[node].anger;
            ps.back().anger %= MOD;
            ns[node].part = ps.size()-1;
            for(auto ch : tree[node]) if(ch != from) see(ch, node);
        };
        see(a, -1);

        ps[ns[b].part].count -= ps.back().count;
        ps[ns[b].part].anger -= ps.back().anger;
        ps[ns[b].part].anger %= MOD;

        ps.back().mult = ps[ns[b].part].mult;

        ps.back().mult *= ps[ns[b].part].count + 1;
        ps.back().mult %= MOD;
        ps[ns[b].part].mult *= ps.back().count + 1;
        ps[ns[b].part].mult %= MOD;

        total += ps[ns[b].part].mult * ps[ns[b].part].anger % MOD;
        total += ps.back().anger * ps.back().mult % MOD;
        total %= MOD;
        total += MOD;
        total %= MOD;

        cout << total << endl;
    }
}
