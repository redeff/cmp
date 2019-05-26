#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> moves = {
	{-1, 0},
	{1, 0},
	{0, 1},
	{0, -1}
};

string names = "UDRL";

const int INF = 2500 * 2500 * 2;

int main() {
	int n, m;
	cin >> n >> m;

	vector<string> board(n+2);
	board[0] = string(m+2, 'O');
	board.back() = string(m+2, 'O');
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		board[i+1] = string(m+2, 'i');
		for(int j = 0; j < m; ++j) board[i+1][j+1] = s[j];
		board[i+1][0] = 'O';
		board[i+1].back() = 'O';
	}

	vector<vector<int>> dist(n+2, vector<int>(m+2, INF));
	vector<pair<int, int>> bfs;
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j)
		if(board[i+1][j+1] == 'M') {
			bfs.emplace_back(i+1, j+1);
			dist[i+1][j+1] = 0;
		}

	int d = 0;
	while(!bfs.empty()) {
		d++;
		vector<pair<int, int>> nbfs;
		for(auto p : bfs) {
			// if(board[p.first][p.second] == 'O') continue;
			// if(dist[p.first][p.second] <= d) continue;
			// dist[p.first][p.second] = d;
			for(auto w : moves) {
				int x = w.first + p.first;
				int y = w.second + p.second;

				if(board[x][y] == 'O') continue;
				if(board[x][y] == '#') continue;
				if(dist[x][y] <= d) continue;
				dist[x][y] = d;
				nbfs.emplace_back(x, y);
			}
		}
		swap(bfs, nbfs);
	}

	/*
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cout << min(dist[i+1][j+1], 9) << " ";
		}
		cout << endl;
	}
	*/

	vector<vector<int>> dir(n+2, vector<int>(m+2, -1));
	bfs.clear();
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j)
		if(board[i+1][j+1] == 'A') {
			bfs.emplace_back(i+1, j+1);
			dir[i+1][j+1] = -2;
		}

	d = 0;
	int gx = -1, gy;
	while(!bfs.empty()) {
		++d;
		vector<pair<int, int>> nbfs;
		for(auto p : bfs) {
			for(int i = 0; i < 4; ++i) {
				int x = moves[i].first + p.first;
				int y = moves[i].second + p.second;
				if(dist[x][y] < d) continue;
				if(board[x][y] == '#') continue;
				if(dir[x][y] != -1) continue;
				dir[x][y] = i;
				if(board[x][y] == 'O') {
					gx = x;
					gy = y;
					goto out;
				}

				nbfs.emplace_back(x, y);
			}
		}

		swap(bfs, nbfs);
	}
	cout << "NO" << endl;
	return 0;
out:;
	cout << "YES" << endl;

	vector<int> res;
	while(dir[gx][gy] != -2) {
		res.push_back(dir[gx][gy]);
		auto p = moves[dir[gx][gy]];
		gx -= p.first;
		gy -= p.second;
	}
	reverse(res.begin(), res.end());
	res.pop_back();
	cout << res.size() << endl;
	for(int i : res) {
		cout << names[i];
	}
	cout << endl;
	// cout << gx << " " << gy << endl;
}
