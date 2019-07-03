#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
	int t;
	cin >> t;
	for(int test = 0; test < t; ++test) {
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

		vector<int> colors(n, 0);
		vector<int> depths(n);
		vector<pair<int, int>> res;
		function<int(int, int)> dfs = [&](int node, int depth) {
			colors[node] = 1;
			depths[node] = depth;

			int lo = n+100;
			for(int ch : graph[node]) {
				// Back edge
				if(colors[ch] == 1 && depths[ch] != depth-1) {
					lo = min(lo, depths[ch]);
				}

				// Tree edge
				else if (colors[ch] == 0) {
					int k = dfs(ch, depth+1);
					if(k > depth)
						res.emplace_back(min(node, ch), max(node, ch));
					lo = min(lo, k);
				}
			}
			colors[node] = 2;

			return lo;
		};

		dfs(0, 0);
		sort(res.begin(), res.end());
		cout << "Caso #" << test+1 << "\n";
		if(res.size() == 0) cout << "Sin bloqueos\n";
		else {
			cout << res.size() << "\n";
			for(auto p : res) cout << p.first+1 << " " << p.second+1 << "\n";
		}
	}
}
