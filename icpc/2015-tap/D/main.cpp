#include <bits/stdc++.h>
#define fore(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

typedef long long ll;

int main() {
	int n, m;
	ll r, e;
	while(cin >> n >> m >> r >> e) {
		vector<vector<int>> graph(n);
		fore(ksadfjlkasdjf, 0, m) {
			int a, b;
			cin >> a >> b;
			--a; --b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		vector<int> colors(n, -1);
		vector<int> size(n, 0);
		vector<int> edges(n, 0);
		function<void(int, int)> dfs = [&](int node, int color) {
			if(colors[node] != -1) return;
			colors[node] = color;
			size[color]++;
			for(int ch : graph[node]) {
				dfs(ch, color);
			}
		};


		fore(i, 0, n) dfs(i, i);
		fore(i, 0, n) {
			edges[colors[i]] += graph[i].size();
			for(int ch : graph[i]) assert(colors[ch] == colors[i]);
		}

		ll total = 0;
		fore(i, 0, n) if(size[i] != 0) {
			total += min(
				(size[i] * (size[i]-1) / 2 - edges[i]/2) * r,
				size[i] * e
			);
		}

		cout << total << endl;
	}
}
