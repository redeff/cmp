#include <bits/stdc++.h>
#define forn(i, n) for(ll i = 0; i < int(n); ++i)
using namespace std;

typedef long long int ll;
const int INF = 3333333;

// Devuelve es árbol de caminos mínimos
vector<ll> dijkstra(ll root, vector<vector<pair<ll, ll>>> &graph) {
    ll n = graph.size();
    vector<ll> dist(n, INF);
    vector<ll> from(n, -1);
    dist[root] = 0;

    auto cmp = [&](ll a, ll b) { return dist[a] < dist[b]; };
    set<ll, decltype(cmp)> node_set(cmp);
    forn(i, n) node_set.insert(i);

    while(!node_set.empty()) {
        ll mn = *node_set.begin();
        node_set.erase(mn);
        for(auto p : graph[mn]) {
            ll new_d = p.second + dist[mn];
            ll to = p.first;
            if(new_d < dist[to]) {
                node_set.erase(to);
                dist[to] = new_d;
                from[to] = mn;
                node_set.insert(to);
            }
        }
    }

    return from;
}

vector<ll> traff(ll root, vector<ll> tree) {
    ll n = tree.size();
    vector<vector<ll>> graph(n);
    forn(i, n) {
        if(tree[i] != -1) {
            graph[tree[i]].push_back(i);
        }
    }

    vector<ll> size_of_subtree(n, -1);

    struct Entry {
        ll i;
        ll sum;
        ll node;
        Entry(ll i_, ll sum_, ll node_): i(i_), sum(sum_), node(node_) {}
    };

    stack<Entry> sk;
    sk.emplace(0, 1, root);
    while(!sk.empty()) {
        if(sk.top().i >= ll(graph[sk.top().node].size())) {
            size_of_subtree[sk.top().node] = sk.top().sum;
            sk.pop();
        } else if(size_of_subtree[graph[sk.top().node][sk.top().i]] != -1) {
            sk.top().sum += size_of_subtree[graph[sk.top().node][sk.top().i]];
            sk.top().i++;
        } else {
            sk.emplace(0, 1, graph[sk.top().node][sk.top().i]);
        }
    }

    /*
    vector<ll> out(n);
    forn(i, n) {
        for(ll t : graph[n]) {
            out[t] = size_of_subtree[t];
        }
    }
    */
    return size_of_subtree;
}

#define ifs cin
#define ofs cout

int main() {
    ifstream ifs("congestion.in");
    ofstream ofs("congestion.out");

    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> weis(n, vector<ll>(n, INF));
    vector<vector<ll>> indx(n, vector<ll>(n, -1));
    vector<vector<ll>> total(n, vector<ll>(n, 0));

    forn(i, m) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--;b--;
        if(weis[a][b] > d) {
            weis[a][b] = d;
            indx[a][b] = i;
        }
    }

    // Adjacency list, de nodes, weis
    vector<vector<pair<ll, ll>>> graph(n);
    forn(i, n) forn(j, n) {
        if(weis[i][j] != INF) {
            graph[i].emplace_back(j, weis[i][j]);
        }
    }

    forn(i, n) {
        vector<ll> tree = dijkstra(i, graph);
        vector<ll> size_of_subtree = traff(i, tree);

        forn(j, n) {
            if(tree[j] != -1) {
                total[tree[j]][j] += size_of_subtree[j];
            }
        }
    }

    ll mx = 0;
    forn(i, n) forn(j, n) {
        mx = max(mx, total[i][j]);
    }

    vector<ll> mxs;
    forn(i, n) forn(j, n) {
        if(total[i][j] == mx) mxs.push_back(indx[i][j]);
    }

    sort(mxs.begin(), mxs.end());

    cout << mxs.size() << " " << mx << endl;
    for(ll id : mxs) cout << id + 1 << " ";
    cout << endl;
}
