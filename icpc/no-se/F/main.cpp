#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

vector<vector<int>> part(vector<vector<int>> board) {
	int n = int(board.size());
	int m = int(board.back().size());

	vector<vector<int>> out(n+1, vector<int>(m+1, 0));
	forn(i, n) forn(j, m) {
		out[i+1][j+1] = out[i+1][j] + out[i][j+1] - out[i][j] + board[i][j];
	}
	return out;
}

int main() {
	int n, m, f;
	while(cin >> n >> m >> f && n != 0) {
		vector<vector<int>> board(n, vector<int>(m));
		forn(i, n) {
			string s;
			cin >> s;
			forn(j, m) board[i][j] = s[j] == '.';
		}

		auto p = part(board);
		auto inrect = [&](int a, int b, int c, int d) {
			return p[c][d] - p[a][d] - p[c][b] + p[a][b];
		};

		int best = 3333333;
		forn(i, n) forn(j, m) {
			int h = i;
			for(int k = m; k >= j; --k) {
				while(inrect(i, j, h, k) < f) {
					++h;
					if(h > n) goto nxt;
				}
				best = min(best, (h - i) * (k - j));
			}
nxt:;
		}
		cout << best << endl;
	}
}
