#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	while(cin >> n >> m) {
		vector<vector<int>> mat(n, vector<int>(m));
		for(auto &v : mat) for(int &i : v) {
			cin >> i;
			--i;
		}

		vector<vector<vector<pair<int, int>>>> trans(n, vector<vector<pair<int, int>>>(n));
		for(int a = 0; a < n; ++a) for(int b = 0; b < n; ++b) {
			for(int i = 0; i < m; ++i) {
				trans[mat[a][i]][mat[b][i]].emplace_back(a, b);
			}
		}

		vector<vector<bool>> seen(n, vector<bool>(n, false));
		function<void(int, int)> dfs = [&](int a, int b) {
			if(seen[a][b]) return;
			seen[a][b] = true;
			for(auto p : trans[a][b]) dfs(p.first, p.second);
		};

		// for(int i = 0; i < n; ++i) dfs(i, i);
		dfs(0, 0);

		bool res = true;
		for(int a = 0; a < n; ++a) for(int b = 0; b < n; ++b) {
			if(!seen[a][b]) res = false;
		}

		if(!res) cout << "N\n";
		else cout << "S\n";
	}
}
