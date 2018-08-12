#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll MOD = 1'000'000'007;

bool bounded_dfs(int &bound, int node, int from, vector<unordered_set<int>> &tree) {
    bound--;
    if(bound <= 0) return false;
    for(auto ch : tree[node]) {
        if(ch != from) {
            if(!dfs(bound, ch, node, tree)) return false;
        }
    }

    return true;
}

int smallest(int u, int v, vector<unordered_set<int>> &tree) {
    tree[u].erase(v);
    tree[v].erase(u);
    atomic<int> res = {-1};
    thread ut(dfs, &res, true, u, -1, &tree);
    thread vt(dfs, &res, true, v, -1, &tree);
    ut.join();
    vt.join();
    for(int k = 0; true; k *= 2) {
        bool a = bounded_dfs(k, )
    }

    return res.load();
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
