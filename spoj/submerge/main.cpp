#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	while(cin >> n >> m && n != 0) {
		vector<vector<int>> graph(n);
		for(int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		vector<int> colors(n, 0);
		vector<int> depths(n);
		vector<int> lows(n, n);
		int total = 0;
		function<void(int, int)> dfs = [&](int node, int depth) {
			colors[node] = 1;
			depths[node] = depth;
			int num_ch = 0;

			bool art = false;
			for(int ch : graph[node]) {
				// Back edge
				if(colors[ch] == 1) {
					lows[node] = min(lows[node], depths[ch]);
				}

				else if(colors[ch] == 0) {
					num_ch++;
					dfs(ch, depth+1);
					if(lows[ch] >= depths[node]) art = true;
					lows[node] = min(lows[node], lows[ch]);
				}
			}

			if(num_ch < 2 && node == 0) art = false;
			if(art) total++;

			colors[node] = 2;
		};

		dfs(0, 0);
		cout << total << endl;
	}
}
