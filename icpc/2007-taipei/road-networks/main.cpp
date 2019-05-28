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

		cin >> m;

		vector<int> depths(n, -1);
		vector<int> colors(n, 0);
		vector<vector<int>> comp(n);

		function<int(int, int)> dfs = [&](int node, int depth) {
			int ret = n+1;
			if(colors[node] == 0) {
				depths[node] = depth;
				colors[node] = 1;
				for(int ch : graph[node]) {
					int r = dfs(ch, depth+1);
					if(depths[node] >= r) {
						// cerr << node << " ~ " << ch << endl;
						comp[node].push_back(ch);
						comp[ch].push_back(node);
					}
					if(depths[node] > r) ret = min(ret, r);
				}
				colors[node] = 2;

				return ret;
			}
			else if(colors[node] == 1) {
				return depths[node];
			}
			else if(colors[node] == 2) return n + 1;
			else {
				cerr << colors[node] << endl;
				assert(false);
				return 0;
			}
			cerr << colors[node] << endl;
			assert(false);
			return 0;
		};

		for(int i = 0; i < n; ++i) {
			dfs(i, 0);
		}

		vector<bool> seen(n, false);
		function<void(int)> dfs2 = [&](int node) {
			if(seen[node]) return;
			seen[node] = true;
			for(int ch : comp[node]) dfs2(ch);
		};

		int total = 0;
		for(int i = 0; i < n; ++i) if(!seen[i]) {
			total++;
			dfs2(i);
		}

		cout << total << endl;
	}
}
