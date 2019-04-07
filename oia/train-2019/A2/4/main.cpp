#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> color(n, 0);

	bool can = true;
	int red = 0;
	function<void(int, int)> dfs = [&](int node, int c) {
		if(color[node] != 0) {
			if(color[node] != c) can = false;
			return;
		}
		color[node] = c;
		if(c == 1) red++;
		for(int ch : graph[node]) dfs(ch, -c);
	};

	for(int i = 0; i < n; ++i) if(color[i] == 0) dfs(i, 1);
	if(!can) {
		cout << -1 << endl;
		return 0;
	}

	cout << red << endl;
	for(int i = 0; i < n; ++i) if(color[i] == 1) cout << 1+i << " ";
	cout << endl;
	cout << n - red << endl;
	for(int i = 0; i < n; ++i) if(color[i] == -1) cout << 1+i << " ";
	cout << endl;
}
