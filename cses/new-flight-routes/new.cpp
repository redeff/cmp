#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

vector<int> leaves(vector<vector<int>> &graph, vector<vector<int>> &hparg) {
	int n = int(graph.size());

	vector<int> ns;
	vector<bool> seen(n, false);
	function<void(int)> dfs1 = [&](int node) {
		if(seen[node]) return;
		seen[node] = true;
		for(int ch: graph[node]) dfs1(ch);
		ns.push_back(node);
	};

	forn(i, n) dfs1(i);
	reverse(ns.begin(), ns.end());

	seen = vector<bool>(n, false);
	vector<int> color = vector<int>(n, -1);
	function<bool(int, int)> dfs2 = [&](int node, int col) {
		bool ret = false;
		if(color[node] != -1 && color[node] != col) ret = true;

		if(seen[node]) return ret;
		seen[node] = true;

		color[node] = col;
		for(int ch : hparg[node]) {
			if(dfs2(ch, col)) ret = true;
		}

		return ret;
	};

	vector<int> res;
	for(int i : ns) {
		if(!seen[i] && !dfs2(i, i)) {
			res.push_back(i);
		}
	}

	return res;
}

vector<int> reach(vector<int> &nodes, vector<vector<int>> &graph) {
	vector<int> color(graph.size(), -1);
	function<void(int, int)> dfs = [&](int node, int col) {
		if(color[node] == -1) return;
		color[node] = col;
		for(int ch : graph[node]) dfs(ch, col);
	};

	for(int i : nodes) dfs(i, i);
	return color;
}

vector<pair<int, int>> eq_graph(
		vector<int> &dads,
		vector<int> &chls,
		vector<vector<int>> &graph) {

	auto dad = reach(dads, graph);
	auto chl = reach(chls, graph);

	vector<pair<int, int>> res;
	for(int d : dads) res.push_back({d, chl[d]});
	for(int c : chls) res.push_back({dad[c], c});

	return res;
}

struct Bunch {
	int head;
	vector<int> body;
};

pair<vector<Bunch>, vector<Bunch>> reduce(
		vector<int> &dads,
		vector<int> &chls,
		vector<pair<int, int>> &graph) {

	int n = int(dads.size());
	vector<int> deg(n, 0);
	for(auto p : graph) {
		deg[p.first]++;
		deg[p.second]++;
	}

	vector<vector<int>> adj;
	for(auto p : graph) {
		if(deg[p.first] == 1 || deg[p.second] == 1) {
			adj[p.first].push_back(p.second);
			adj[p.second].push_back(p.first);
		} else {
			deg[p.first]--;
			deg[p.second]--;
		}
	}

	forn(i, n) if(adj[]) {
		
	}
}

int main(){}
