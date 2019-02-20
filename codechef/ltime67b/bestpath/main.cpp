#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll INF = 333333333333;

int main() {
	int test;
	cin >> test;
	for(int testcase = 0; testcase < test; ++testcase) {
		int n, m;
		cin >> n >> m;
		vector<vector<ll>> floyd(n, vector<ll>(n, INF));
		for(int i = 0; i < n; ++i) floyd[i][i] = 0;
		vector<pair<pair<int, int> ll>> ni;
		for(int i = 0; i < m; ++i) {
			int u, v;
			ll w;
			cin >> u >> v >> w;
			u--;
			v--;
			ni.push_back({{u, v}, w});
		}

		for(int i = 0; i < n; ++i) {
			for(auto p : ni) {
				
			}
		}

		for(int x = 0; x < n; ++x) {
			for(int a = 0; a < n; ++a) {
				for(int b = 0; b < n; ++b) {
					floyd[a][b] = min(floyd[a][b], floyd[a][x] + floyd[x][b]);
				}
			}
		}

		for(int x = 0; x < n; ++x) {
			ll min_come = INF;
			ll min_go = INF;
			for(int i = 0; i < n; ++i) {
				min_come = min(min_come, floyd[i][x]);
				min_go = min(min_go, floyd[x][i]);

				if(floyd[x][i] < INF/2 || floyd[i][x] < INF/2) if(floyd[i][i] < 0) {
					cout << "INF" << endl;
					goto outer;
				}
			}

			cout << min_come + min_go << endl;
outer:;
		}
	}
}
