#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;

typedef pair<int, int> pii;

// Returns the minimum path tree
vector<int> dijkstra(int s, vector<vector<pii>> &graph) {
    int n = int(graph.size());

    vector<int> dist(n, INF);
    dist[s] = 0;

    vector<int> from(n, -1);

    vector<bool> visited(n, false);

    priority_queue<pii> pq;
    pq.push({0, s});

    while(!pq.empty()) {
        int node = pq.top().second;
        // int dist = pq.top().first;
        pq.pop();

        if(!visited[node]) {
            for(auto nei: graph[node]) {
                if(dist[node] + nei.second < dist[nei.first]) {
                    dist[nei.first] = dist[node] + nei.second;
                    pq.push({dist[node] + nei.second, nei.first});
                    from[nei.first] = node;
                }
            }
            visited[node] = true;
        }
    }

    /*
    for(auto v: visited) {
        cerr << v << " ";
    } cerr << endl;

    for(auto v: dist) {
        cerr << v << " ";
    } cerr << endl;
    */

    return from;
}

#define ifs cin
#define ofs cout

int main() {
    ifstream ifs("congestion.in");
    ofstream ofs("congestion.out");
    int m, n;
    cin >> n >> m; 

    vector<vector<pii>> graph(n);
    vector<map<int, int>> indices(n);
    for(int i = 0; i < m; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        graph[a].emplace_back(b, d);
        indices[a][b] = i;
    }

    vector<map<int, int>> total(n);

    for(int k = 0; k < n; ++k) {
        vector<int> dp(n, -1);

        auto from = dijkstra(k, graph);

        vector<vector<int>> mint(n);
        for(int i = 0; i < n; ++i) {
            if(from[i] != -1) 
                mint[from[i]].push_back(i);
            // else
                // cerr << "------------------1 " << i << endl;
        }


        struct Frame {
            int node;
            int i;
            int sum;
            Frame(int node_, int i_, int sum_): node(node_), i(i_), sum(sum_) {}
        };

        stack<Frame> sk;
        sk.emplace(k, 0, 0);
        while(!sk.empty()) {
            Frame &frame = sk.top();
            if(frame.i >= int(mint[frame.node].size())) {
                dp[frame.node] = frame.sum + int(mint[frame.node].size());
                // cerr << frame.node << " " << dp[frame.node] << endl;
                sk.pop();
            } else if(dp[mint[frame.node][frame.i]] == -1) {
                // cerr << "rec " << mint[frame.node][frame.i] << endl;
                sk.emplace(mint[frame.node][frame.i], 0, 0);
            } else {
                frame.sum += dp[mint[frame.node][frame.i]];
                frame.i++;
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int c : mint[i]) {
                total[i][c] += dp[c] + 1;
                // cout << i << " " << c << " Y " << total[i][c] << endl;
            }
        }
    }

    int sum = 0;
    int mx = -INF;
    for(auto& i: total) {
        for(auto j : i) {
            sum += j.second;
            mx = max(mx, j.second);
        }
    }

    vector<int> mxs;
    for(int i = 0; i < n; ++i) {
        for(auto j : total[i]) {
            if(mx == j.second) {
                // cout << indices[i][j.first] + 1 << " ";
                mxs.push_back(indices[i][j.first]);
            }
        }
    }
    cout << mxs.size() << " " << mx << endl;
    for(int i : mxs) cout << i + 1 << " ";
    cout << endl;
}
