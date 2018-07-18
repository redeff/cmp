#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll INF = 333333333;

int flog(int n) {
    return 8 * sizeof(int) - 1 - __builtin_clz(n);
}

struct Snode;

struct Idx {
    int n;
    ll val;

    Idx dads(int k, vector<Snode> &stree);
};

Idx join(Idx a, Idx b) {
    return {b.n, max(a.val, b.val)};
}

struct Snode {
    int depth;
    vector<Idx> dads;
};

Idx Idx::dads(int k, vector<Snode> &stree) {
    Idx t = stree[n].dads[k];
    return join(*this, t);
}

Idx kth_dad(Idx node, int k, vector<Snode> &stree) {
    for(int i = 0; (1 << i) <= k; ++i) if((1 << i) & k) {
        node = node.dads(i, stree);
    }
    return node;
}

ll dist(Idx a, Idx b, vector<Snode> &stree) {
    if(stree[a.n].depth > stree[b.n].depth) swap(a, b);

    b = kth_dad(b, stree[b.n].depth - stree[a.n].depth, stree);

    if(a.n == b.n) return join(a, b).val;

    for(int k = stree[a.n].dads.size() - 1; k >= 0; --k) {
        if(a.dads(k, stree).n != b.dads(k, stree).n) {
            a = a.dads(k, stree);
            b = b.dads(k, stree);
        }
    }

    a = a.dads(0, stree);
    b = b.dads(0, stree);
    assert(a.n == b.n);

    return join(a, b).val;
}

struct Conn {
    int a;
    int b;
    ll wei;
};

vector<Snode> build(int n, vector<Conn> &conns) {
    vector<vector<pair<int, ll>>> tree(n);
    vector<Snode> stree(n);
    int sdepth = flog(n) + 5;

    for(int i = 0; i < n; ++i) {
        stree[i].depth = 0;
        stree[i].dads = vector<Idx>(sdepth);
    }

    for(auto c : conns) {
        tree[c.a].push_back({c.b, c.wei});
        tree[c.b].push_back({c.a, c.wei});
    }

    vector<bool> seen(n, false);
    function<void(int)> see = [&](int node) {
        seen[node] = true;
        for(auto ch: tree[node]) if(!seen[ch.first]) {
            stree[ch.first].depth = stree[node].depth + 1;
            stree[ch.first].dads[0] = {node, ch.second};
            see(ch.first);
        }
    };

    see(0);
    stree[0].dads[0] = {0, INF};

    for(int k = 1; k < sdepth; ++k) {
        for(int i = 0; i < n; ++i) {
            Idx nxt = stree[i].dads[k-1];
            stree[i].dads[k] = join(nxt, stree[nxt.n].dads[k-1]);
        }
    }

    return stree;
}

struct UFnode {
    int dad;
    int wei;
};

vector<UFnode> make_uf(int n) {
    vector<UFnode> uf(n);
    for(int i = 0; i < n; ++i) {
        uf[i].dad = i;
        uf[i].wei = 0;
    }
    return uf;
}

int repr(int a, vector<UFnode> &uf) {
    int r = a;
    while(uf[r].dad != r) r = uf[r].dad;
    int b = a;
    while(b != r) {
        int c = uf[b].dad;
        uf[b].dad = r;
        b = c;
    }

    return r;
}

void join(int a, int b, vector<UFnode> &uf) {
    a = repr(a, uf);
    b = repr(b, uf); 
    if(uf[a].wei < uf[b].wei) swap(a, b);
    if(uf[a].wei == uf[b].wei) uf[a].wei++;
    uf[b].dad = a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int n, m, h;
        cin >> n >> m >> h;
        if(n == -1) break;

        vector<Conn> conns(m);
        for(int i = 0; i < m; ++i) {
            int a, b;
            ll wei;
            cin >> a >> b >> wei;
            a--; b--;
            conns[i].a = a;
            conns[i].b = b;
            conns[i].wei = wei;
        }

        vector<Conn> sorted = conns;
        sort(sorted.begin(), sorted.end(), [](Conn a, Conn b){return a.wei < b.wei;});

        vector<Conn> mst;
        auto uf = make_uf(n);
        ll size = 0;
        for(auto conn : sorted) {
            if(repr(conn.a, uf) != repr(conn.b, uf)) {
                join(conn.a, conn.b, uf);
                mst.push_back(conn);
                size += conn.wei;
            }
        }

        auto stree = build(n, mst);
        for(int i = 0; i < h; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            cout << dist({a, -INF}, {b, -INF}, stree) << " ";
        }
        cout << endl;
    }
}
