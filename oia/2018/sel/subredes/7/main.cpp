#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose2(ll a) {
    return a * (a - 1ll) / 2ll;
}

void process(vector<vector<bool>> &graph) {
    ll n = graph.size();
    vector<ll> trigs(n, 0);

    ll diamonds = 0;

    for(int a = 0; a < n; ++a) {
        if(a % 100 == 0) cerr << a << endl;
        for(int b = 0; b < a; ++b) if(graph[a][b]) {
            ll common = 0;
            for(int c = 0; c < n; ++c) if(graph[a][c] && graph[b][c]) {
                if(c < b) {
                    trigs[a]++;
                    trigs[b]++;
                    trigs[c]++;
                }
                common++;
            }
            diamonds += choose2(common);
        }
    }

    ll total = 0;
    for(int i = 0; i < n; ++i) {
        total += choose2(trigs[i]);
    }

    cout << (total - 2 * diamonds) << endl;
}

#include "../mat.h"

int main() {
    parse();
}
