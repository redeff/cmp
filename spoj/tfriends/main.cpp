#include <bits/stdc++.h>
using namespace std;

const int N = 100;

bool graph[N][N];

int main() {
	int t;
	cin >> t;
	while(t --> 0) {
		int n;
		cin >> n;

		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			for(int j = 0; j < n; ++j) {
				graph[i][j] = s[j] == 'Y';
			}
		}

		vector<int> ord;
		vector<bool> seen(n, false);
		function<void(int)> dfs1 = [&](int node) {
			if(seen[node]) return;
			seen[node] = true;
			for(int i = 0; i < n; ++i) if(graph[node][i]) dfs1(i);
			ord.push_back(node);
		};

		for(int i = 0; i < n; ++i) dfs1(i);
		reverse(ord.begin(), ord.end());

		seen = vector<bool>(n, false);
		function<void(int)> dfs2 = [&](int node) {
			if(seen[node]) return;
			seen[node] = true;
			for(int i = 0; i < n; ++i) if(graph[i][node]) dfs2(i);
		};

		int total = 0;
		for(int i : ord) if(!seen[i]) {
			dfs2(i);
			total++;
		}
		cout << total << endl;
	}
}
