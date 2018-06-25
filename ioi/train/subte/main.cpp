#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Conn {
    int to;
    ll wei;
};

const ll INF = 333333333333333;

int main() {
#ifndef MIO
    freopen("subte.in", "r", stdin);
    freopen("subte.out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;
    vector<vector<Conn>> graph(n);
    vector<int> deg(n, 0);
    vector<ll> dist(n, -INF);
    vector<int> conn(n, 0);
    vector<bool> killed(n, false);
    ll cost = 0;

    for(int i = 0; i < n-1; ++i) {
        int a, b;
        ll l;
        cin >> a >> b >> l;
        a--; b--;
        graph[a].push_back(Conn {b, l});
        graph[b].push_back(Conn {a, l});
        deg[a]++;
        deg[b]++;
        cost += l;
    }

    auto loss = [&](int a) -> ll {
        return graph[a][conn[a]].wei + dist[a];
    };

    auto cmp = [&](int a, int b) {
        return loss(a) > loss(b);
    };

    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    for(int i = 0; i < n; ++i) {
        if(graph[i].size() == 1) {
            dist[i] = 0;
            pq.push(i); 
        }
    }

    ll mx = 0;
    while(cost > k) {
        int k = pq.top();
        pq.pop();
        ll ls = loss(k);
        mx = ls;
        killed[k] = true;

        Conn c = graph[k][conn[k]];
        cost -= c.wei;

        dist[c.to] = ls;
        deg[c.to]--;
        if(deg[c.to] == 1) {
            for(int i = 0; i < int(graph[c.to].size()); ++i)
                if(!killed[graph[c.to][i].to])
                    conn[c.to] = i;
            pq.push(c.to);
        }
    }

    // Se me terminaron los edges
    // Aparentemente tiene q haber al menor un edge updateado
    cout << mx << endl;
}
