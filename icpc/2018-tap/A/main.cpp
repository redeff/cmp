#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

vector<vector<pair<int, int>>> jumps = {
	{{-3, 0}, {0, 3}, {0, -3}, {3, 0}},
	{{-3, 0}, {0, 2}, {0, -2}, {3, 0}},
	{{-2, 0}, {0, 3}, {0, -3}, {2, 0}},
};

string dirs = "DLRU";

int main() {
	int n, m;
	cin >> n >> m;
	vector<string> board(n);
	for(string &s: board) cin >> s;

	vector<vector<bool>> empty(2*n-1, vector<bool>(2*m-1, true));

	forn(i, n) forn(j, m) empty[2*i][2*j] = (board[i][j] != '#');
	forn(i, n-1) forn(j, m)
		empty[2*i+1][2*j] = (board[i][j] != '#' && board[i+1][j] != '#');
	forn(i, n) forn(j, m-1)
		empty[2*i][2*j+1] = (board[i][j] != '#' && board[i][j+1] != '#');

	pair<int, int> start;
	pair<int, int> end;

	vector<vector<bool>> seen(2*n-1, vector<bool>(2*m-1, false));
	vector<vector<int>> from(2*n-1, vector<int>(2*m-1, -1));

	forn(i, n) forn(j, m)
		if(board[i][j] == 'E') start = {2*i, 2*j};
		else if(board[i][j] == 'C') end = {2*i, 2*j};

	vector<pair<int, int>> bfs = {start};
	seen[start.first][start.second] = true;
	int len = 0;
	while(!bfs.empty()) {
		vector<pair<int, int>> nbfs;
		for(auto p : bfs) {
			assert(0 <= p.first);
			assert(p.first < 2*n-1);
			assert(0 <= p.second);
			assert(p.second < 2*m-1);
			assert(empty[p.first][p.second]);

			if(p == end) goto done;
			// if(seen[p.first][p.second]) continue;
			// seen[p.first][p.second] = true;
			int index = p.first%2+p.second%2*2;
			assert(index < 3);

			int cnt = 0;
			for(auto q : jumps[index]) {
				int a = p.first + q.first;
				int b = p.second + q.second;
				if(true
						&& 0 <= a
						&& a < 2*n-1
						&& 0 <= b
						&& b < 2*m-1
						&& empty[a][b]
						&& !seen[a][b]) {
					seen[a][b] = true;
					from[a][b] = cnt;
					nbfs.emplace_back(a, b);
				}
				++cnt;
			}
		}

		swap(bfs, nbfs);
		len++;
	}

	cout << -1 << endl;
	return 0;

done:;
	string res = "";
	while(end != start) {
		/*
		auto brd = board;
		brd[end.first/2][end.second/2] = 'O';
		brd[(end.first+1)/2][(end.second+1)/2] = 'O';
		for(string s : brd) cout << s << endl;
		cout << endl;
		*/
		int index = end.first%2+end.second%2*2;
		int k = from[end.first][end.second];
		// if(k == -1) break;
		assert(k != -1);
		assert(index < 3);
		auto p = jumps[index][k];
		res += dirs[k];
		end.first -= p.first;
		end.second -= p.second;
	}
	cout << len << endl;
	cout << res << endl;
}
