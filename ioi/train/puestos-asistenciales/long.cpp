#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct BiConn {
    int a;
    int b;
    ll wei;
};

struct Conn {
    int to;
    ll wei;
};

void dfs(int node, int len, vector<ll> &dist, vector<vector<Conn>> &tree) {
    if(len >= dist[node]) return;
    dist[node] = len;
    for(auto ch : tree[node]) {
        dfs(ch.to, len + ch.wei, dist, tree);
    }
}

const ll INF = 333333;

vector<ll> calc_dist(int node, vector<vector<Conn>> &tree) {
    vector<ll> dist(tree.size(), INF);
    dfs(node, 0, dist, tree);
    return dist;
}

int main() {
#ifndef YO
    freopen("puesto.in", "r", stdin);
    freopen("puesto.out", "w", stdout);
#endif
    int m;
    cin >> m;

    vector<int> ns;

    vector<BiConn> conns(m);
    for(int i = 0; i < m; ++i) {
        cin >> conns[i].a >> conns[i].b >> conns[i].wei;
        ns.push_back(conns[i].a);
        ns.push_back(conns[i].b);
    }

    sort(ns.begin(), ns.end());
    ns.erase(unique(ns.begin(), ns.end()), ns.end());
    int n = ns.size();

    for(int i = 0; i < m; ++i) {
        conns[i].a = lower_bound(ns.begin(), ns.end(), conns[i].a) - ns.begin();
        conns[i].b = lower_bound(ns.begin(), ns.end(), conns[i].b) - ns.begin();
    }

    vector<vector<Conn>> tree(n);
    for(auto c : conns) {
        tree[c.a].push_back({c.b, c.wei});
        tree[c.b].push_back({c.a, c.wei});
    }

    vector<ll> dist_from_origin = calc_dist(0, tree);
    int fst = max_element(dist_from_origin.begin(), dist_from_origin.end()) - dist_from_origin.begin();

    vector<ll> dist_from_fst = calc_dist(fst, tree);
    int snd = max_element(dist_from_fst.begin(), dist_from_fst.end()) - dist_from_fst.begin();

    vector<ll> dist_from_snd = calc_dist(snd, tree);
    double diam = (double) dist_from_fst[snd];
    cout << fixed;
    cout << setprecision(1);
    cout << diam / 2.0 << endl;
    // cerr << mx << " " << ns[mx] << " " << oth << " " << ns[oth] << endl;

    // El diámetro es mx <-> oth

    for(auto c : conns) {
        int a = dist_from_fst[c.a] - dist_from_snd[c.a]; 
        int b = dist_from_fst[c.b] - dist_from_snd[c.b]; 

        if(a < 0 && b > 0 || a > 0 && b < 0) cout << "0";
        else {

            // if(abs(a) > abs(b)) cout << "+";
            // else cout << "-";
            if(a + b > 0) {
                if(dist_from_fst[c.a] < dist_from_fst[c.b]) cout << "-";
                else cout << "+";
            } else {
                if(dist_from_snd[c.a] < dist_from_snd[c.b]) cout << "-";
                else cout << "+";
            }
        }
    }
}
