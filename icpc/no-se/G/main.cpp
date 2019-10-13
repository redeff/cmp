#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

vector<pair<int, int>> dirs = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 0},
	{1, -1},
	{0, -1}
};

int main() {
	int n, m;
	while(cin >> n >> m && n+m != 0) {
		vector<string> board(n);
		for(string &s: board) cin >> s;

		vector<bool> wrong(n*m, false);
		vector<vector<int>> cols(n, vector<int>(m, 0));
		vector<vector<int>> cmps(n, vector<int>(m, -1));
		function<void(int,int,int,int)> dfs =
			[&](int x, int y, int cmp, int col) {
				if(x < 0 || x >= n || y < 0 || y >= m) return;
				if(board[x][y] == '.') return;
				if(cols[x][y] == -col) {
					wrong[cmps[x][y]] = true;
					return;
				}
				if(cols[x][y] == col) return;
				assert(cols[x][y] == 0);
				cols[x][y] = col;
				cmps[x][y] = cmp;
				for(auto d : dirs) {
					int xx = x + d.first;
					int yy = y + d.second;
					dfs(xx, yy, cmp, -col);
				}
			};

		forn(i, n) forn(j, m) {
			if(board[i][j] == 'I') dfs(i, j, i * m + j, 1);
		}

		cout << endl;
		forn(i, n) {
			forn(j, m) {
				if(board[i][j] == '.') cout << '.';
				else if(cols[i][j] == 0) cout << 'F';
				else if(wrong[cmps[i][j]]) cout << 'B';
				else if(cols[i][j] == 1) cout << '(';
				else if(cols[i][j] == -1) cout << ')';
				else assert(false);
			}
			cout << endl;
		}
	}
}
