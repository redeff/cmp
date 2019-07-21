#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mat(n, vector<int>(m));
	unordered_map<int> slots;
	for(auto &v : mat) for(auto &i : v) {
		cin >> i;
		slots.insert(i);
	}

	vector<pair<int, int>> edges;
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(mat[0][j] != mat[i][j]) {
				edges.push_back({mat[0][j], mat[i][j]});
				goto done;
			}
		}
		cout << "No\n";
		return 0;
done:;
	}

	unordered_set<int> nodes;
	unordered_map<int, unordered_set<int>> graph;
	for(auto e : edges) {
		nodes.insert(e.first);
		nodes.insert(e.second);
		graph[e.first].insert(e.second);
		graph[e.second].insert(e.first);
	}

	unordered_map<int, unordered_map<int>> colors;
	for(int i : nodes) {
		color[i] = {i};
	}

	while(graph.size() > 40) {
		for(auto &pe : graph) for(auto &qe : graph) {
			int p = pe.first;
			int q = qe.first;
			if(p != q && !graph[p].count(q)) {
				for(int i : graph[q]) {
					graph[p].insert(i);
					graph[i].insert(p);
				}
				graph.erase(q);
				uni.push_back({p, q});

				for(int c : colors[q]) colors[p].insert(c);
				goto nxt;
			}
		}
		assert(false);
nxt:;
	}

	for(int i : slots) if
}
