#include <bits/stdc++.h>
using namespace std;

bool query(vector<vector<int>> graph, int a, int b, int c, int d) {
	int n = graph.size();
	vector<bool> seen(n, false);
	function<void(int)> dfs = [&](int node) {
		if(node == c && d == -1) return;
		if(seen[node]) return;
		seen[node] = true;
		for(int ch : graph[node]) {
			if(node == c && ch == d || node == d && ch == c) {
;
			} else {
				dfs(ch);
			}
		}
	};

	dfs(a);
	return seen[b];
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		int a, b, c, d, t;
		cin >> t >> a >> b >> c;
		--a; --b; --c;
		if(t == 1) {
			cin >> d;
			--d;
		}
		else d = -1;
		if(query(graph, a, b, c, d)) {
			cout << "da" << endl;
		} else {
			cout << "ne" << endl;
		}
	}
}
