#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int INF = 3333333;

// Floor of log2(n)
int flg(int n) {
    return 8 * (sizeof (int)) - __builtin_clz(n) - 1;
}
struct BiConn {
    int to;
    int from;
    ll wei;
};

struct Conn {
    int to;
    ll wei;
};

vector<vector<Conn>> to_adj_list(int n, vector<BiConn> &graph) {
    vector<vector<Conn>> tree(n);
    for(BiConn b : graph) {
        tree[b.from].push_back({.to=b.to, .wei=b.wei});
        tree[b.to].push_back({.to=b.from, .wei=b.wei});
    }
    return tree;
}

struct Node {
    Conn dad;
    // vector<Conn> ch;
    int depth;
};

vector<Node> root_at(int n, int root, vector<vector<Conn>> &tree) {
    vector<Node> rtree(n);
    vector<bool> visited(n, false);
    rtree[root].dad = Conn {.to=root, .wei=INF};

    function<void(int, int)> visit = [&](int node, int depth) {
        visited[node] = true;
        rtree[node].depth = depth;
        for(Conn ch: tree[node]) {
            if(!visited[ch.to]) {
                visit(ch.to, depth + 1);
                // rtree[node].ch.push_back(ch);
            } else {
                rtree[node].dad = ch;
            }
        }
    };

    visit(root, 0);
    return rtree;
}

struct SparseNode {
    int depth;
    vector<Conn> ans;
};

vector<SparseNode> sparse(int n, int ln, vector<Node> &rtree) {
    vector<SparseNode> stree(n);
    for(int i = 0; i < n; ++i) {
        stree[i].ans    = vector<Conn>(ln);
        stree[i].ans[0] = rtree[i].dad;
        stree[i].depth  = rtree[i].depth;
    }

    for(int k = 1; k < ln; ++k) {
        for(int i = 0; i < n; ++i) {
            stree[i].ans[k] = 
                Conn {
                    .to=stree[stree[i].ans[k-1].to].ans[k-1].to,
                    .wei=stree[stree[i].ans[k-1].to].ans[k-1].wei
                        + stree[i].ans[k-1].wei
                };
        }
    }

    return stree;
}

#define DEPTH(n) stree[n].depth
#define ANS(n, k) stree[n].ans[k].to

ll dist(vector<SparseNode> &stree, int a, int b) {
    if(DEPTH(a) > DEPTH(b)) {
        auto c = a;
        a = b;
        b = c;
    }

    ll dist = 0;

    while(DEPTH(a) != DEPTH(b)) {
        dist += stree[b].ans[flg(DEPTH(b) - DEPTH(a))].wei;
        b = ANS(b, flg(DEPTH(b) - DEPTH(a)));
    }

    if(a == b) return dist;
    else {
        for(int s = stree[a].ans.size() - 1; s >= 0; --s) {
            if(ANS(a, s) != ANS(b, s)) {
                dist += stree[a].ans[s].wei;
                dist += stree[b].ans[s].wei;
                a = ANS(a, s);
                b = ANS(b, s);
            }
        }
    }

    return dist + stree[a].ans[0].wei + stree[b].ans[0].wei;
}

int main() {
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        vector<BiConn> graph;
        for(int i = 0; i < n - 1; ++i) {
            int a;
            ll l;
            cin >> a >> l;
            // a--;
            graph.push_back(BiConn {.to=a, .from=i+1, .wei=l});
        }

        auto tree = to_adj_list(n, graph);
        auto rtree = root_at(n, 0, tree);
        auto stree = sparse(n, flg(n) + 1, rtree);

        int q;
        cin >> q;
        for(int i = 0; i < q; ++i) {
            int a, b;
            cin >> a >> b;
            // a--; b--;
            cout << dist(stree, a, b);
            if(i != q - 1) cout << " ";
        }
        cout << endl;
    }
}
