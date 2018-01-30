#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;

struct Edge {
    int to;
    int wei;
    Edge(int to_, int wei_): to(to_), wei(wei_) {}
};

vector<int> dijkstra(int root, vector<vector<Edge>> &graph) {
    int n = int(graph.size());

    vector<int> visited(n, false);
    vector<int> from(n, -1);
    vector<int> dists(n, INF);
    dists[root] = 0;

    priority_queue<pair<int, int>> es;
    es.emplace(0, root);
    while(!es.empty()) {
        int node = es.top().second;
        es.pop();

        if(!visited[node]) {
            for(auto ed: graph[node]) {
                if(dists[ed.to] > dists[node] + ed.wei) {
                    dists[ed.to] = dists[node] + ed.wei;
                    es.emplace(dists[ed.to], ed.to);
                    from[ed.to] = node;
                }
            }
            visited[node] = true;
        }
    }

    return from;
}

vector<int> dp;
int get_size_subtree(int node, vector<vector<int>> &tree) {
    if(dp[node] != -1) return dp[node];
    int total = 1;
    for(int i = 0; i < tree[node].size(); ++i) {
        total += get_size_subtree(tree[node][i], tree);
    }
    dp[node] = total;
    return total;
}

/*
#define ifs cin
#define ofs cout
*/
int main() {
    ifstream ifs("congestion.in");
    ofstream ofs("congestion.out");
    int m, n;
    cin >> n >> m; 

    vector<vector<Edge>> graph(n);
    vector<unordered_map<int, pair<int, int>>> indices(n);
    // vector<map<int, int>> indices(n);
    vector<int> total(m, 0);
    for(int i = 0; i < m; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        graph[a].emplace_back(b, d);
        if(indices[a].count(b) == 0 || indices[a][b].second > d) {
            indices[a][b] = {i, d};
        }
    }

    for(int root = 0; root < n; ++root) {
        auto from = dijkstra(root, graph);
        vector<vector<int>> tree(n);
        for(int i = 0; i < n; ++i) {
            if(i != root) {
                tree[from[i]].push_back(i);
            } else if(from[i] != -1) assert(false); 
        }
        dp = vector<int>(n, -1);

        for(int i = 0; i < n; ++i) {
            if(i != root) {
                total[indices[from[i]][i].first] += get_size_subtree(i, tree);
            }
        }
    }
    int mx = *max_element(total.begin(), total.end());
    vector<int> mxs;
    for(int i = 0; i < m; ++i) {
        if(total[i] == mx) mxs.push_back(i);
    }

    cout << mxs.size() << " " << mx << endl;
    for(auto i: mxs) cout << i + 1 << " ";
    cout << endl;
}
