#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k, m;
	while(cin >> n >> k >> m && n != -1) {
		vector<vector<int>> graph(n);
		vector<int> opened_by(n, -1);
		vector<int> opens(n, -1);
		for(int i = 0; i < k; ++i) {
			int a, b;
			cin >> a >> b;
			a--;b--;
			opens[a] = b;
			opened_by[b] = a;
		}

		for(int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			a--;b--;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		vector<bool> seen(n, false);
		vector<bool> opened(n, false);
		vector<bool> expa(n, false);
		// seen[0] = true;
		vector<int> bfs = {0};
		while(!bfs.empty()) {
			vector<int> nbfs;
			for(int node : bfs) {
				if(expa[node]) continue;
				expa[node] = true;

				if(opens[node] != -1) {
					opened[opens[node]] = true;
					if(seen[opens[node]]) nbfs.push_back(opens[node]);
				}

				for(int ch : graph[node]) {
					seen[ch] = true;
					if(opened_by[ch] == -1 || opened[ch]) nbfs.push_back(ch);
				}
			}

			swap(nbfs, bfs);
		}

		if(expa.back()) cout << "Y" << endl;
		else cout << "N" << endl;
	}
}
