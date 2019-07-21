#include <bits/stdc++.h>
#define fore(i, z, n) for(int i = int(z); i < int(n); ++i)
using namespace std;

typedef unsigned long long int ll;

int main() {
	int n, m;
	cin >> n >> m;
	string ns;
	cin >> ns;
	assert(int(ns.size()) == n);
	++n;

	vector<vector<int>> graph(n);
	fore(i, 0, m) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
	}

	int s, f;
	cin >> s >> f;
	--s; --f;
	graph[f].push_back(ns.size());
	f = ns.size();
	ns.push_back('#');

	vector<int> topo;
	vector<int> seen(n, 0);
	function<int(int)> dfs = [&](int node) {
		if(seen[node]) return seen[node];
		if(node == f) {
			topo.push_back(f);
			seen[node] = 2;
			return 2;
		}
		seen[node] = 1;
		for(int ch : graph[node]) seen[node] = max(seen[node], dfs(ch));
		if(seen[node] == 2) topo.push_back(node);
		return seen[node];
	};

	if(dfs(s) != 2) {
		cout << "No way" << endl;
		return 0;
	}

	// for(int i : topo) cout << i << " ";
	unordered_set<int> gd;
	for(int i : topo) gd.insert(i);
	// cout << endl;
	/*
	for(int i = 0; i < n; ++i) for(int j : graph[i]) {
		cout << i << " -> " << j << endl;
	}
	*/

	int LCA = 20;
	struct Dad {
		int node;
		ll ash;
	};

	vector<vector<Dad>> dads(n);
	function<bool(int,int)> comp = [&](int a, int b) -> bool {
		if(a == b) return false;
		// if(a == f) return true;
		// if(b == f) return false;
		int i = 0;
		while(dads[a][i].ash == dads[b][i].ash && i < LCA) ++i;
		--i;
		if(i == -1) {
			assert(ns[a] != ns[b]);
			return ns[a] < ns[b];
		}
		return comp(dads[a][i].node, dads[b][i].node);
	};

	for(int node : topo) {
		int best;
		if(node == f) best = node;
		else {
			bool emp = true;
			for(int i : graph[node]) if(gd.count(i)) {
				if(emp) best = i, emp = false;
				else {
					best = min(best, i, comp);
				}
			}
		}
		/*
		int best = graph[node].size() ?
			*min_element(graph[node].begin(), graph[node].end(), comp):
			node;
			*/
		dads[node].push_back(Dad {best, (ll)ns[node]});
		ll po = 19823ll;
		for(int l = 0; l < LCA; ++l) {
			Dad d = dads[node][l];
			dads[node].push_back(Dad {
					dads[d.node][l].node,
					d.ash + po * dads[d.node][l].ash
					});
			po *= po;
		}
		assert(dads[node].size() == LCA+1);
	}

	string res;
	while(s != f) {
		res.push_back(ns[s]);
		s = dads[s][0].node;
	}
	cout << res << endl;
}
