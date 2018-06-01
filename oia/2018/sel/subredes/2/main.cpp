#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose2(ll a) {
    return a * (a - 1ll) / 2ll;
}

void process(vector<unordered_set<int>> &graph) {
    ll edges = 0;
    ll vs = 0; // Edge adjacent to another edge
    for(auto& node : graph) {
        edges += node.size();
        vs += choose2(node.size());
    }
    edges /= 2;
    cout << (choose2(edges) - vs) << endl;
}

#include "../main.h"

int main() {
    parse();
}
