#include <vector>
#include <iostream>
using namespace std;

vector<pair<int, int>> dir = {
	{-1, 0},
	{0, -1},
	{0, 1},
	{1, 0},
};

string names = "DRLU";

int main() {
	int n, m;
	cin >> n >> m;
	vector<string> board(n);
	for(string &s : board) cin >> s;

	struct Rem {
		pair<int, int> pos;
		char d;
	};
	vector<vector<Rem>>
		from(n, vector<Rem>(m, Rem {make_pair(0, 0), 'O'}));
	vector<pair<int, int>> bfs;
	
	pair<int, int> to = {0, 0};
	for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
		if(board[x][y] == 'B') bfs.emplace_back(x, y);
		if(board[x][y] == 'A') to = {x, y};
	}

	while(bfs.size() != 0) {
		vector<pair<int, int>> nbfs;
		for(auto p : bfs) {
			if(board[p.first][p.second] == '#') continue;
			for(int i = 0; i < dir.size(); ++i) {
				int x = p.first + dir[i].first;
				int y = p.second + dir[i].second;
				if(0 <= x && x < n && 0 <= y && y < m) {
					if(from[x][y].d == 'O') {
						from[x][y] = {p, names[i]};
						nbfs.emplace_back(x, y);
					}
				}
			}
		}
		swap(bfs, nbfs);
	}

	if(from[to.first][to.second].d == 'O') {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		string cs;
		while(board[to.first][to.second] != 'B') {
			cs.push_back(from[to.first][to.second].d);
			to = from[to.first][to.second].pos;
		}

		cout << cs.size() << endl;
		cout << cs << endl;
	}
}
