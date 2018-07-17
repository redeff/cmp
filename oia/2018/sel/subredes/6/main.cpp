#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose2(ll a) {
    return a * (a - 1ll) / 2ll;
}

void process(vector<vector<bool>> &graph) {
    ll n = graph.size();
    vector<ll> trigs(n, 0);
    for(int a = 0; a < n; ++a) {
        if(a % 100 == 0) cerr << a << endl;
        for(int b = 0; b < a; ++b) if(graph[a][b]) {
            for(int c = 0; c < b; ++c) if(graph[a][c] && graph[b][c]) {
                trigs[a]++;
                trigs[b]++;
                trigs[c]++;
            }
        }
    }

    ll total = 0;
    for(int i = 0; i < n; ++i) {
        ll cnt = 0;
        for(int j = 0; j < n; ++j) if(graph[i][j]) cnt++;
        total += trigs[i] * (cnt - 2);
    }

    cout << total << endl;
}

#include "../mat.h"

int main() {
    parse();
}
