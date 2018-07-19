#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dag(n);
    vector<int> indegree(n, 0);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        dag[a].push_back(b);
        indegree[b]++;
    }

    priority_queue<int> blob;
    for(int i = 0; i < n; ++i) {
        if(indegree[i] == 0) blob.push(-i);
    }

    vector<int> topo;
    while(!blob.empty()) {
        auto p = -blob.top();
        topo.push_back(p);
        blob.pop();
        for(int ch : dag[p]) {
            indegree[ch]--;
            if(indegree[ch] == 0) blob.push(-ch);
        }
    }

    if(topo.size() == n) {
        for(int t : topo) cout << t+1 << " ";
        cout << endl;
    } else cout << "Sandro fails.\n";
}
