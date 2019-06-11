#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dir = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<string> board(n);
	for(string &s : board) cin >> s;

	vector<vector<bool>> seen(n, vector<bool>(m, false));
	function<void(int, int)> dfs = [&](int x, int y) {
		if(x < 0 || n <= x) return;
		if(y < 0 || m <= y) return;
		if(board[x][y] == '#') return;

		if(seen[x][y]) return;
		seen[x][y] = true;

		for(auto d : dir) {
			dfs(x + d.first, y + d.second);
		}
	};

	int total = 0;
	for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
		if(board[x][y] != '#' && !seen[x][y]) {
			dfs(x, y);
			total++;
		}
	}

	cout << total << endl;
}
