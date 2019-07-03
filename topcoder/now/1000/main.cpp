#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
};

class TombExplorer {
public:
	int minimumDigging(vector<string> board) {
		int n = board.size();
		int m = board[0].size();

		vector<vector<int>> chamber(n, vector<int>(m, -1));

		auto in_range = [&](int x, int y) {
			return 0 <= x && x < n && 0 <= y && y < m;
		};

		function<void(int, int, int)> dfs1 = [&](int x, int y, int col) {
			chamber[x][y] = col;
			for(auto d : dirs) {
				int a = x + d.first;
				int b = y + d.second;
				if(in_range(a, b) && chamber[a][b] == -1 && board[a][b] == '.') {
					dfs1(a, b, col);
				}
			}
		};

		int ch = 0;
		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			if(board[x][y] == '.' && chamber[x][y] == -1) {
				dfs1(x, y, ch);
				++ch;
			}
		}

		vector<vector<int>> graph(ch, vector<int>(ch, 3333333));
		vector<bool> used(ch, false);
		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			if(board[x][y] == '.' && !used[chamber[x][y]]) {
				used[chamber[x][y]] = true;
				// int c = chamber[x][y];
				vector<pair<int, int>> bfs = {{x, y}};
				int d = 0;
				vector<vector<bool>> seen(n, vector<bool>(m, false));
				while(!bfs.empty()) {
					vector<pair<int, int>> nbfs;
					for(int i = 0; i < bfs.size(); ++i) {
						auto p = bfs[i];
						if(board[p.first][p.second] == '.') {
							int s = chamber[x][y];
							int t = chamber[p.first][p.second];
							graph[s][t] = min(graph[s][t], d);
						}
						if(seen[p.first][p.second]) continue;
						seen[p.first][p.second] = true;
						for(auto di : dirs) {
							int a = p.first + di.first;
							int b = p.second + di.second;
							if(in_range(a, b)) {
								if(board[a][b] == '.') bfs.emplace_back(a, b);
								else nbfs.emplace_back(a, b);
							}
						}
					}
					++d;
					swap(bfs, nbfs);
				}
			}
		}

		vector<int> ord(ch);
		for(int i = 0; i < ch; ++i) ord[i] = i;

		// return ch;
		int res = 33333333;
		do {
			int total = 0;
			for(int i = 1; i < ch; ++i) total += graph[ord[i-1]][ord[i]];
			res = min(total, res);
		} while(next_permutation(ord.begin(), ord.end()));

		return res;
	}
};

