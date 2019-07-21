#include <bits/stdc++.h>
using namespace std;

struct Max {
	int mx;
	int num;
	void insert(int n) {
		if(n == mx) {
			num ++;
		}
		else if(n > mx) {
			num = 1;
			mx = n;
		}
	}

	void add(int n) {
		mx += n;
	}

	void join(Max ma) {
		if(mx < ma.mx) {
			mx = ma.mx;
			num = ma.num;
		} else if(mx == ma.mx) {
			num += ma.num;
		}
	}

	Max() {
		mx = -33333333;
		num = 0;
	}
};



int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int test;
	cin >> test;
	while(test --> 0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> board(n, vector<int>(m));
		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			cin >> board[x][y];
			board[x][y] *= 2;
			board[x][y] -= 1;
		}

		vector<vector<int>> part(n+1, vector<int>(m+1));
		for(int x = 0; x <= n; ++x) for(int y = 0; y <= m; ++y) {
			if(x > 0 && y > 0) {
				part[x][y] = part[x-1][y] + part[x][y-1] - part[x-1][y-1] + board[x-1][y-1];
			} else {
				part[x][y] = 0;
			}
		}

		Max total;
		auto rect = [&](int x1, int x2, int y1, int y2) {
			int big = part[x2][y2] - part[x1][y2] - part[x2][y1] + part[x1][y1];
			// x2--; y2--;
			// x1--; y1--;
			// int small = part[x2][y2] - part[x1][y2] - part[x2][y1] + part[x1][y1];
			// return big - small;
			return big;
		};

		for(int a = 0; a < n; ++a) for(int b = a+2; b <= n; ++b) {
			Max loc;
			// cerr << a << " ab " << b << endl;
			for(int y = 2; y <= m; ++y) {
				loc.add(rect(a, b, y-1, y) - rect(a+1, b-1, y-2, y-1));
				loc.insert(rect(a, b, y-2, y));
				// cerr << loc.mx << " - " << loc.num << endl;
				total.join(loc);
			}
		}

		for(int a = 0; a < n; ++a) for(int b = a+2; b <= n; ++b) {
			for(int y = 0; y < m; ++y) total.insert(rect(a, b, y, y+1));
		}

		for(int a = 0; a < m; ++a) for(int b = a+2; b <= m; ++b) {
			for(int y = 0; y < n; ++y) total.insert(rect(y, y+1, a, b));
		}

		for(int a = 0; a < n; ++a) for(int b = 0; b < m; ++b) {
			total.insert(board[a][b]);
		}

		cout << total.mx << " " << total.num << endl;
	}
}
