#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose3(ll a) {
    return a * (a - 1ll) * (a - 2ll) / 6ll;
}

void process(vector<unordered_set<int>> &graph) {
    ll total = 0;
    for(int a = 0; a < graph.size(); ++a) {
        if(a % 100 == 0) cerr << a << endl;
        // for(int b = 0; b < a; ++b) {
        for(int b : graph[a]) if(b < a) {
            ll common = 0;
            for(int i : graph[a]) {
                if(graph[b].count(i) == 1) common++;
            }
            total += choose3(common);
        }
    }
    cout << total << endl;
}

#include "../main.h"

int main() {
    parse();
}
