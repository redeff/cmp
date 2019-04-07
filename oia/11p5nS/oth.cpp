// #include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
using namespace std;

struct Dp {
	int x;
	int y;
	int size;
	int operator< (const Dp a) const {
		return size < a.size;
	}
};

int main() {
#ifndef LOCAL
#define cin asjdfahssdlfkj
#define cout lksadflkjasld
	ifstream cin("yurumi.in");
	ofstream cout("yurumi.out");
#endif

	int n, m, x;
	cin >> n >> m >> x;
	vector<vector<array<Dp, 2>>> dp = vector<vector<array<Dp, 2>>>(n, vector<array<Dp, 2>>(m, {Dp {}, Dp {}}));
	vector<vector<bool>> board(n, vector<bool>(m, false));
	for(int i = 0; i < x; ++i) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		board[x][y] = true;
	}

	function<bool(int, int)> isin = [&](int x, int y) {
		return 0 <=x && x < n && 0 <= y && y < m;
	};

	for(int side = 0; side < 2; ++side) {
		int d = 2 * side - 1;
		for(int x = side ? 0 : n-1; x != (side ? n : -1); x += d) {
			for(int y = side ? 0 : m-1; y != (side ? m : -1); y += d) {
				if(board[x][y]) {
					dp[x][y][side].size = 0;
					continue;
				}
				int one = isin(x - d, y) ? dp[x - d][y][side].size : 0;
				int two = isin(x, y - d) ? dp[x][y - d][side].size : 0;
				int three = isin(x - d, y - d) ? dp[x - d][y - d][side].size : 0;
				dp[x][y][side].size = min(one, min(two, three)) + 1;
			}
		}

		/*
		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < m; ++y) {
				cerr << "(" << dp[x][y][side].size << ") ";
			}
			cerr << endl;
		}
		*/

		for(int x = side ? 0 : n-1; x != (side ? n : -1); x += d) {
			for(int y = side ? 0 : m-1; y != (side ? m : -1); y += d) {
				dp[x][y][side].x = side ? x - dp[x][y][side].size + 1 : x;
				dp[x][y][side].y = side ? y - dp[x][y][side].size + 1 : y;

				if(isin(x - d, y)) {
					dp[x][y][side] = max(dp[x][y][side], dp[x-d][y][side]);
				}
				if(isin(x, y - d)) {
					dp[x][y][side] = max(dp[x][y][side], dp[x][y-d][side]);
				}
			}
		}
	}


	int biggest = 0;
	Dp resa;
	Dp resb;
	for(int side = 0; side < 2; ++side) {
		for(int i = 0; i < (side ? n-1 : m-1); ++i) {
			Dp a = side ? dp[i+1][0][0] : dp[0][i+1][0];
			Dp b = side ? dp[i][m-1][1] : dp[n-1][i][1];
			if(a.size * a.size + b.size * b.size > biggest) {
				biggest = a.size * a.size + b.size * b.size;
				resa = a;
				resb = b;
			}
		}
	}

	cout << resa.x << " " << resa.y << " " << resa.size << "\n";
	cout << resb.x << " " << resb.y << " " << resb.size << "\n";
}
