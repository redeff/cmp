#include <bits/stdc++.h>
using namespace std;

void testcase() {
	int n;
	cin >> n;
	vector<vector<int>> tree(n);
	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	int root = -1;
	for(int i = 0; i < n; ++i) if(tree[i].size() == 1) root = i; // Set root to a leaf;

	vector<int> colors(n, 0);

	int d = 0;

	bool second_step = false;

	function<void(int, int)> dfs = [&](int node, int color) {
		if(second_step && d == 0) return;
		if(colors[node] != color) {
			d -= colors[node];
			d += color;
			colors[node] = color;
			for(int ch : tree[node]) dfs(ch, -color);
		}
	};

	dfs(root, 1);
	int k = d == 0 ? 1 : 2;
	second_step = true;
	dfs(root, -1);
	cout << k << endl;
	for(int i = 0; i < n; ++i) if(colors[i] == 1) cout << i + 1 << " ";
	cout << endl;
	for(int i = 0; i < n; ++i) if(colors[i] == -1) cout << i + 1 << " ";
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i) testcase();
}
