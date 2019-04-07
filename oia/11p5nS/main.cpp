#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
#define cin asjdfahssdlfkj
#define cout lksadflkjasld
	ifstream cin("yurumi.in");
	ofstream cout("yurumi.out");
#endif

	int n, m, x;
	cin >> n >> m >> x;

	vector<vector<int[2][3]>> dp(n, vector<int[2][3]>(m));
	vector<vector<bool>> board(n, vector<bool>(m, false));
	for(int i = 0; i < x; ++i) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		board[x][y] = true;
	}

	function<bool(int, int)> isin = [&](int x, int y) {
		return 0 <= x && x < n && 0 <= y && y < m;
	};

	for(int side = 0; side < 2; ++side) {
		int d = 2 * side - 1;
		int fromx = (n + d) % (n + 1);
		for(int x = fromx; x != fromx + n * d; x += d) {
			int fromy = (m + d) % (m + 1);
			for(int y = fromy; y != fromy + m * d; y += d) {
				int one = isin(x - d, y) ? dp[x - d][y][side][0] : 0;
				int two = isin(x, y - d) ? dp[x][y - d][side][0] : 0;
				int three = min(one, two);
				if(!board[x - three][y - three]) dp[x][y][side][0] = three + 1;
				else dp[x][y][side][0] = 0;
			}
		}

		for(int x = fromx; x != fromx + n * d; x += d) {
			int fromy = (m + d) % (m + 1);
			for(int y = fromy; y != fromy + m * d; y += d) {
				int one = isin(x - d, y) ? dp[x - d][y][side][0] : 0;
				int two = isin(x, y - d) ? dp[x][y - d][side][0] : 0;
				int three = dp[x][y][side][0];
				dp[x][y][side][0] = max(three, max(one, two));
				if(three >= one && three >= two) {
					dp[x][y][side][1] = side == 0 ? x - three + 1 : x;
					dp[x][y][side][2] = side == 0 ? y - three + 1 : y;
				} else if(one >= two) {
					dp[x][y][side][1] = dp[x - d][y][side][1];
					dp[x][y][side][2] = dp[x - d][y][side][2];
				} else {
					dp[x][y][side][1] = dp[x][y - d][side][1];
					dp[x][y][side][2] = dp[x][y - d][side][2];
				}
			}
		}
	}

	int best = 0;
	int x1, y1, s1;
	int x2, y2, s2;
	for(int i = 0; i < 2; ++i) {
		for(int x = 1; x < (i?n:m)-1; ++x) {
			int (*dpa)[2][3] = i ? &dp[x+1][0] : &dp[0][x+1];
			int (*dpb)[2][3] = i ? &dp[x-1][m-1] : &dp[n-1][x-1];
			int s1t = (*dpa)[0][0];
			int s2t = (*dpb)[0][0];
			if(s1t * s1t + s2t * s2t > best) {
				best = s1t * s1t + s2t * s2t;
				s1 = s1t;
				s2 = s2t;
				x1 = (*dpa)[0][1];
				y1 = (*dpa)[0][2];

				x2 = (*dpb)[0][1];
				y2 = (*dpb)[0][2];
			}
		}
	}
	cerr << x1 << " " << y1 << " " << s1 << endl;
	cerr << x2 << " " << y2 << " " << s2 << endl;
}
