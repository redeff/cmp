#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;
typedef long long int ll;
/*
struct Edge {
    int to;
    int wei;
    Edge(int to_, int wei_): to(to_), wei(wei_) {}
};
*/

// return the distances for every pair of nodes
vector<ll> dijkstra(int root, vector<unordered_map<int, ll>> &graph) {
    int n = int(graph.size());

    vector<bool> visited(n, false);
    vector<ll> dists(n, INF);
    dists[root] = 0;

    priority_queue<pair<ll, int>> es;
    es.emplace(0, root);
    while(!es.empty()) {
        int node = es.top().second;
        es.pop();

        if(!visited[node]) {
            for(auto ed: graph[node]) {
                if(dists[ed.first] > dists[node] + ed.second) {
                    dists[ed.first] = dists[node] + ed.second;
                    es.emplace(dists[ed.first], ed.first);
                }
            }
            visited[node] = true;
        }
    }

    return dists;
}

vector<ll> dp;
ll get_size_subtree(int node, vector<unordered_set<int>> &dag) {
    if(dp[node] != -1) return dp[node];
    ll total = 1;
    // for(int i = 0; i < tree[node].size(); ++i) {
    for(auto ch: dag[node]) {
        total += get_size_subtree(ch, dag);
    }
    dp[node] = total;
    return total;
}

#define ifs cin
#define ofs cout
int main() {
    ifstream ifs("congestion.in");
    ofstream ofs("congestion.out");
    int m, n;
    cin >> n >> m; 

    vector<unordered_map<int, ll>> graph(n);
    vector<unordered_map<int, pair<int, ll>>> indices(n);

    struct Edge {
        int from;
        int to;
        int len;
        int id;
        Edge(int from_, int to_, int len_, int id_): from(from_), to(to_), len(len_), id(id_) {}
    };

    vector<Edge> edges;
    // vector<map<int, int>> indices(n);
    // vector<int> total(m, 0);
    vector<unordered_map<int, ll>> total(n);
    for(int i = 0; i < m; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        // cerr << a << " " << b;

        // graph[a].emplace_back(b, d);
        if(indices[a].count(b) == 0 || indices[a][b].second > d) {
            graph[a][b] = d;
            indices[a][b] = {i, d};
        }
        edges.emplace_back(a, b, d, i);
    }

    for(int root = 0; root < n; ++root) {
        auto dists = dijkstra(root, graph);
        vector<unordered_set<int>> dag(n);
        /*
        for(int i = 0; i < n; ++i) {
            if(i != root) {
                dag[from[i]].push_back(i);
            } else if(from[i] != -1) assert(false); 
        }
        */
        dp = vector<ll>(n, -1);

        for(auto e : edges) {
            if(dists[e.from] + e.len == dists[e.to]) {
                dag[e.from].insert(e.to);
            }
        }

        for(int i = 0; i < n; ++i) {
            for(auto ch: dag[i]) {
                total[i][ch] += get_size_subtree(ch, dag);
            }
        }
    }
    // int mx = *max_element(total.begin(), total.end());
    ll mx = -INF;
    for(int i = 0; i < n; ++i) for(auto t : total[i]) mx = max(mx, t.second);
    vector<int> mxs;
    for(int i = 0; i < m; ++i) {
        // if(total[i] == mx) mxs.push_back(i);
        if(total[edges[i].from][edges[i].to] == mx && edges[i].len == graph[edges[i].from][edges[i].to]) {
            mxs.push_back(i);
        }
    }

    cout << mxs.size() << " " << mx << endl;
    for(auto i: mxs) cout << i + 1 << " ";
    cout << endl;
}
