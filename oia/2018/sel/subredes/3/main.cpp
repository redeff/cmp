#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll choose2(ll a) {
    return a * (a - 1ll) / 2ll;
}

void process(vector<unordered_set<int>> &graph) {
    ll total = 0;
    for(int a = 0; a < graph.size(); ++a) {
        for(int b : graph[a]) {
            if(a < b) {
                total += (graph[a].size() - 1) * (graph[b].size() - 1); 
                for(int i : graph[a]) {
                    if(graph[b].count(i) == 1) total--;
                }
            }
        }
    }
    cout << total << endl;
}

#include "../main.h"

int main() {
    parse();
}
