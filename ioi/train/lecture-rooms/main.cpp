#include <bits/stdc++.h>
using namespace std;

int flog(int x) {
    return 8 * sizeof(int) - 1 - __builtin_clz(x);
}

struct Snode {
    int depth;
    int size; // Size of subtree
    vector<int> dads;
};

int kth_dad(int n, int k, vector<Snode> &stree) {
    for(int i = 0; (1 << i) <= k; ++i) {
        if(k & (1 << i)) {
            n = stree[n].dads[i];
        }
    }
    return n;
}

int lca(int a, int b, vector<Snode> &stree) {
    if(stree[a].depth > stree[b].depth) swap(a, b);
    b = kth_dad(b, stree[b].depth - stree[a].depth, stree);
    if(a == b) return a;
    
    for(int k = int(stree[a].dads.size()) - 1; k >= 0; --k) {
        if(stree[a].dads[k] != stree[b].dads[k]) {
            a = stree[a].dads[k];
            b = stree[b].dads[k];
        }
    }
    return stree[a].dads[0];
}

int dist(int a, int b, vector<Snode> &stree) {
    int l = lca(a, b, stree);
    return stree[a].depth + stree[b].depth - 2 * stree[l].depth;
}

int calc(int a, int b, vector<Snode> &stree) {
    if(a == b) return stree.size();

    if(stree[a].depth > stree[b].depth) swap(a, b);

    int d = dist(a, b, stree);
    if(d % 2 != 0) return 0;

    if(stree[a].depth == stree[b].depth) {
        int prv_a = kth_dad(a, d/2 - 1, stree);
        int prv_b = kth_dad(b, d/2 - 1, stree);
        return stree.size() - stree[prv_a].size - stree[prv_b].size;
    } else {
        int prv = kth_dad(b, d/2 - 1, stree);
        int mid = stree[prv].dads[0];
        return stree[mid].size - stree[prv].size;
    }
}

vector<Snode> build(int n, vector<pair<int, int>> &conns) {
    vector<vector<int>> tree(n);
    vector<Snode> stree(n);
    int sdepth = flog(n) + 5;

    for(int i = 0; i < n; ++i) {
        stree[i].size = 1;
        stree[i].dads = vector<int>(sdepth);
        stree[i].depth = 0;
    }

    for(auto p : conns) {
        tree[p.first].push_back(p.second);
        tree[p.second].push_back(p.first);
    }

    vector<bool> seen(n, false);

    function<void(int)> see = [&](int node) {
        seen[node] = true;
        for(auto ch : tree[node]) if(!seen[ch]) {
            stree[ch].depth = stree[node].depth + 1;
            stree[ch].dads[0] = node;
            see(ch);
            stree[node].size += stree[ch].size;

        }
    };

    stree[0].dads[0] = 0;
    see(0);

    for(int k = 1; k < sdepth; ++k) {
        for(int i = 0; i < n; ++i) {
            stree[i].dads[k] = stree[stree[i].dads[k-1]].dads[k-1];
        }
    }

    return stree;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> conns(n-1);
    for(int i = 0; i < n-1; ++i) {
        cin >> conns[i].first >> conns[i].second;
        conns[i].first--;
        conns[i].second--;
    }

    auto stree = build(n, conns);

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << calc(a, b, stree) << endl;
    }
}
