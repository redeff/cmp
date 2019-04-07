#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> ps(n);
	vector<vector<int>> graph(n);
	for(int i = 0; i < n; ++i) {
		cin >> ps[i];
		ps[i]--;
	}
	reverse(ps.begin(), ps.end());
	vector<int> inv_ps(n);
	for(int i = 0; i < n; ++i) inv_ps[ps[i]] = i;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		if(inv_ps[u] > inv_ps[v]) graph[u].push_back(v);
	}

	vector<bool> alive(n, true);
	int alives = 1;
	for(int i = 1; i < n; ++i) {
		int alive_i_can_cross = 0;
		for(int ch : graph[ps[i]]) if(alive[ch]) alive_i_can_cross++;
		if(alive_i_can_cross == alives) alive[ps[i]] = false;
		else alives++;
	}

	cout << n - alives << endl;
}
