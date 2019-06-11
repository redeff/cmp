#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll BOUND = 'Z' - 'A' + 1;
ll mat[BOUND][BOUND];
char to[BOUND][BOUND];
ll INF = 1e9;

const ll MAXN = 200;
ll dp[MAXN][MAXN][BOUND];

int main() {
	int n;
	while(cin >> n && n != 0) {
		string s;
		for(int i = 0; i < n; ++i) {
			string c;
			cin >> c;
			s.push_back(c[0]);
		}

		for(int i = 0; i < BOUND; ++i) for(int j = 0; j < BOUND; ++j) {
			mat[i][j] = INF;
		}

		// cerr << s << endl;

		for(int i = 0; i < BOUND; ++i) for(int j = 0; j < BOUND; ++j) to[i][j] = 'i';
		for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
			int x = s[i] - 'a';
			int y = s[j] - 'a';
			cin >> mat[x][y] >> to[x][y] >> to[x][y];
		}


		int m;
		cin >> m;
		for(int kaka = 0; kaka < m; ++kaka) {
			string ss;
			cin >> ss;
			int k = ss.size();

			for(int i = 0; i < k; ++i) {
				for(int j = 0; j < k; ++j) {
					for(int c = 0; c < BOUND; ++c) {
						dp[i][j][c] = INF;
					}
				}
			}

			for(int i = 0; i < k; ++i) {
				dp[i][i][ss[i] - 'a'] = 0;
			}
			for(int i = k-1; i >= 0; --i) {
				for(int j = i+1; j < k; ++j) {
					for(char a : s) {
						a -= 'a';
						for(int b : s) {
							b -= 'a';
							for(int t = i; t < j; ++t) {
								int c = to[a][b] - 'a';
								// if(mat[a][b] != INF)
									// cerr << a << " " << b << " " << mat[a][b] << endl;
								dp[i][j][c] = min(
										dp[i][j][c],
										dp[i][t][a] + dp[t+1][j][b] + mat[a][b]);
							}
						}
					}
				}
			}

			// for(int i = 0; i < BOUND; ++i) cout << dp[0][k-1][i] << " ";
			// cout << endl;
			char best;
			int be = INF;
			for(char c : s) {
				if(dp[0][k-1][c - 'a'] < be) {
					be = dp[0][k-1][c - 'a'];
					best = c;
				}
			}
			cout << be << "-" << best << endl;
			// cout << *min_element(dp[0][k-1], dp[0][k-1]+BOUND) << endl;
		}
		cout << endl;
	}
}
