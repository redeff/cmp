#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)
int inf = 333333;

char rev(char c) {
	if(c == 'o' || c == 'v' || c == 'w' || c == 'x') return c;
	if(c == 'p') return 'q';
	if(c == 'q') return 'p';
	if(c == 'b') return 'd';
	if(c == 'd') return 'b';
	cerr << c << endl;
	assert(false);
}

int dp[1010][1010][2];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	while(cin >> n) {
		string a, b;
		cin >> b >> a;
		// cerr << a << "\n" << b << endl;

		// vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n+1, t>(2,inf)));
		// vector<vector<int[2]>> dp(n+1, vector<int[2]>(n+1, {0, 0}));
		forn(j, n+1) {
			forn(i, n+1) {
				forn(k, 2) {
					dp[i][j][k] = inf;
				}
			}
		}

		dp[0][0][0] = 0;
		forn(j, n+1) {
			forn(i, n+1) {
				if(i > 0 && j > 0 && a[i-1] == b[j-1])
					dp[i][j][0] = min(dp[i][j][0], dp[i-1][j-1][0]);

				if(i > 0 && j+n-i >= 0 && j+n-i < n && a[i-1] == rev(b[j+n-i]))
					dp[i][j][1] = min(dp[i][j][1], dp[i-1][j][1]);

				forn(k, 2) dp[i][j][k] = min(dp[i][j][k], dp[i][j][1-k]+1);
			}
		}

		/*
		forn(i, n+1) {
			forn(j, n+1) {
				cerr << dp[i][j][0] << " ";
			}
			cerr << endl;
		}

		cerr << endl;

		forn(i, n+1) {
			forn(j, n+1) {
				cerr << dp[i][j][1] << " ";
			}
			cerr << endl;
		}
		*/

		int mn = inf;
		forn(j, n+1) mn = min(mn, min(dp[n][j][0], dp[n][j][1]));
		cout << (mn == inf ? -1 : mn) << "\n";
	}
}
