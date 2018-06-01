#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose3(ll a) {
    return a * (a - 1ll) * (a - 2ll) / 6ll;
}


void process(vector<unordered_set<int>> &graph) {
    ll sum = 0;
    for(auto& node : graph) {
        sum += choose3(node.size());
    }
    cout << sum << endl;
}

#include "../main.h"

int main() {
    parse();
}
