#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 33333333;

// Devuleve la distancia de cada nodo a root
vector<ll> dijkstra(vector<vector<pair<ll, ll>>> &adj, ll root) {
    ll n = ll(adj.size());
    vector<ll> dist(n, INF);
    dist[root] = 0;
    // vector<ll> from(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> dj;
    dj.push({0, root});

    while(!dj.empty()) {
        ll nearest_node = dj.top().second;
        // cerr << nearest_node << endl;
        dj.pop();
        if(!visited[nearest_node]) {
            for(auto nei: adj[nearest_node]) {
                if(dist[nearest_node] + nei.second < dist[nei.first]) {
                    // from[nei.first] = nearest_node;
                    dist[nei.first] = dist[nearest_node] + nei.second;
                    dj.push({dist[nei.first], nei.first});
                }
            }

            visited[nearest_node] = true;
        }
    }

    return dist;
}

// Dado graph, que tiene que ser un dag, encuentra el número
// de rutas entre a y e recursivamente y con dp
ll get_ways(ll s, ll e, vector<vector<ll>> &graph) {
    ll n = ll(graph.size());
    auto dp = vector<ll>(n, -1);

    struct Frame {
        ll node;
        ll i;
        ll sum;
        Frame(ll node_, ll i_, ll sum_): node(node_), i(i_), sum(sum_) {}
    };

    dp[e] = 1;

    stack<Frame> sk;
    sk.emplace(s, 0, 0);

    int times = 0;
    while(!sk.empty()) {
        Frame &frame = sk.top();
        if(frame.i >= ll(graph[frame.node].size())) {
            dp[frame.node] = frame.sum;
            sk.pop();
        } else if(dp[graph[frame.node][frame.i]] == -1) {
            sk.emplace(graph[frame.node][frame.i], 0, 0);
            times++;
            if(times > n + 10) return 0;
        } else {
            frame.sum += dp[graph[frame.node][frame.i]];
            frame.i++;
        }
    }

    return dp[s];
}

#define cin ifs
#define cout ofs

int main() {
    ifstream ifs("ambulancia.in");
    ofstream ofs("ambulancia.out");

    ll n, t, s, e;
    cin >> n >> t;
    cin >> s >> e;
    
    s--; e--;

    //                Dest, wheight
    vector<vector<pair<ll, ll>>> adj(n);
    for(ll i = 0; i < t; ++i) {

        ll a, b, d;
        cin >> a >> b >> d;
        a--; b--;

        adj[a].emplace_back(b, d);
        adj[b].emplace_back(a, d);
    }

    // Las sidtancias a S y a E
    auto dist_s = dijkstra(adj, s);
    auto dist_e = dijkstra(adj, e);

    vector<vector<ll>> graph(n);
    for(ll i = 0; i < n; ++i) {
        for(auto nei: adj[i]) {
            ll j = nei.first;

            // A cada arista la pongo en graph si y solo si
            // esa arista te acerca a E y te aleja de S, es claro
            // que esto forma un dag (si siempre te acercas no puede
            // haber un loop)
            if(dist_s[i] < dist_s[j] && dist_e[i] > dist_e[j]) {
                graph[i].push_back(j);
            }
        }
    }

    cout << get_ways(s, e, graph) << endl;
}
