#include<bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;
ll inf = 333333333333;

int main() {
	int n, e;
	while(cin >> n >> e) {
		vector<vector<ll>> mat(e, vector<ll>(e));
		forn(i, e) forn(j, e) cin >> mat[i][j];

		vector<int> colors(n, -1);
		forn(i, e) {
			int k;
			cin >> k;
			forn(j, k) {
				int p;
				cin >> p;
				colors[p-1] = i;
			}
		}

		vector<vector<int>> graph(n);
		forn(aksjdhlakjd, n-1) {
			int a, b;
			cin >> a >> b;
			--a; --b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		vector<vector<ll>> dp(n, vector<ll>(e, inf));
		function<void(int, int)> dfs = [&](int node, int dad) {
			for(int ch: graph[node]) if(ch != dad) {
				dfs(ch, node);
			}

			forn(i, e) {
				if(colors[node] == -1 || colors[node] == i) {
					dp[node][i] = 0;
					for(int ch: graph[node]) if(ch != dad) {
						ll best = inf;
						forn(j, e) {
							best = min(best, dp[ch][j] + mat[i][j]);
						}
						dp[node][i] += best;
					}
				}
			}
		};

		dfs(0, 0);
		cout << *min_element(dp[0].begin(), dp[0].end()) << endl;
	}
}
