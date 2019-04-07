#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	vector<vector<ll>> as(n, vector<ll>(m));
	vector<vector<ll>> bs(n, vector<ll>(m));

	for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) cin >> as[x][y];
	for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) cin >> bs[x][y];

	vector<vector<ll>> diag_a(n + m-1);
	vector<vector<ll>> diag_b(n + m-1);
	for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
		diag_a[x+y].push_back(as[x][y]);
		diag_b[x+y].push_back(bs[x][y]);
	}

	for(auto &v : diag_a) sort(v.begin(), v.end());
	for(auto &v : diag_b) sort(v.begin(), v.end());

	if(diag_a == diag_b) cout << "YES" << endl; else cout << "NO" << endl;
}
