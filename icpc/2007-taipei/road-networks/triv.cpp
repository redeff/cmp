#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t --> 0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> graph(n);

		for(int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			graph[a-1].push_back(b-1);
		}

		vector<vector<bool>> seen(n, vector<bool>(n, false));
		for(int i = 0; i < n; ++i) {
			function<void(int)> dfs = [&](int node) {
				if(seen[i][node]) return;
				seen[i][node] = true;
				for(int ch : graph[node]) dfs(ch);
			};

			dfs(i);
		}

		vector<bool> s(n);
		function<void(int)> dfs = [&](int node) {
			if(s[node]) return;
			s[node] = true;
			for(int i = 0; i < n; ++i) if(seen[i][node] && seen[node][i]) dfs(i);
		};

		int total = 0;
		for(int i = 0; i < n; ++i) if(!s[i]) {
			total++;
			dfs(i);
		}

		cin >> m;
		cout << total << endl;
	}
}
