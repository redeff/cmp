#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose2(ll a) {
    return a * (a - 1ll) / 2ll;
}

void process(vector<unordered_set<int>> &graph) {
    ll total = 0;
    for(int a = 0; a < graph.size(); ++a) {
        if(a % 100 == 0) cerr << a << endl;
        for(int b = 0; b < a; ++b) {
            ll common = 0;
            for(int i : graph[a]) {
                if(graph[b].count(i) == 1) common++;
            }
            total += choose2(common);
        }
    }
    cout << total / 2 << endl;
}

#include "../main.h"

int main() {
    parse();
}
