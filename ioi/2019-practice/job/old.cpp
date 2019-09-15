#include "job.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < int(n); ++i)

template<class V>
void join(V &a, V &b) {
	if(a.size() < b.size()) swap(a, b);
	for(int i : b) a.insert(i);
}

long long scheduling_cost(vector<int> dads, vector<int> costs, vector<int> times) {
	auto cmp = [&](int a, int b) {
		return costs[a]*times[b] < costs[b]*times[a];
	};

	int n = int(dads.size());
	vector<vector<int>> graph(n);
	vector<set<int, decltype(cmp)>> children(n, set<int, decltype(cmp)>(cmp));
	fore(i, 1, n) graph[dads[i]].push_back(i);

	function<void(int)> dfs = [&](int node) {
		for(int ch : graph[node]) {
			dfs(ch);
			children[node].insert(ch);
		}
		while(!children[node].empty() && cmp(*children[node].begin(), node)) {
			int t = *children[node].begin();
			chidren[node].erase(children[node].begin());
			join(children[node], children[t]);
		}
	};
	return 0;
}
