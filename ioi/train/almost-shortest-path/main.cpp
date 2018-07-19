#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;

struct Conn {
    int to;
    int wei;
};

bool operator<(Conn a, Conn b) {
    return a.wei > b.wei;
}

int main() {
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0) break;

        int s, e;
        cin >> s >> e;

        vector<vector<Conn>> graph(n, vector<Conn>(0));
        vector<vector<Conn>> trans(n, vector<Conn>(0));
        for(int i = 0; i < m; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            graph[a].push_back({b, w});
            trans[b].push_back({a, w});
            // graph[b].push_back({a, w});
        }

        vector<int> to_s(n, INF);
        vector<int> to_e(n, INF);

        for(int i = 0; i < 2; ++i) {
            int source = i == 0 ? s : e;
            vector<int> &dist = i == 0 ? to_s : to_e;
            auto &gr = i == 0 ? graph : trans;
            // dist[source] = 0;

            priority_queue<Conn> dij;
            dij.push({source, 0});

            while(!dij.empty()) {
                auto p = dij.top();
                dij.pop();

                if(dist[p.to] > p.wei) {
                    dist[p.to] = p.wei;
                    for(auto c : gr[p.to]) {
                        dij.push({c.to, c.wei + p.wei});   
                    }
                }
            }
        }


        int source = s;
        vector<int> dist(n, INF);

        priority_queue<Conn> dij;
        dij.push({source, 0});

        while(!dij.empty()) {
            auto p = dij.top();
            dij.pop();

            if(dist[p.to] > p.wei) {
                dist[p.to] = p.wei;
                for(auto c : graph[p.to]) if(c.wei + to_s[p.to] + to_e[c.to] != to_s[e]) {
                    dij.push({c.to, c.wei + p.wei});   
                }
            }
        }

        cout << (dist[e] == INF ? -1 : dist[e]) << endl;
    }
}
