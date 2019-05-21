#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n);
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<vector<int>> tree(n);
	vector<vector<int>> dads(n);

	vector<int> ord;
	vector<bool> seen(n, false);
	vector<int> bfs = {0};
	dads[0].push_back(0);
	while(!bfs.empty()) {
		int t = bfs.back();
		bfs.pop_back();
		if(seen[t]) continue;
		seen[t] = true;
		ord.push_back(t);
		for(int ch : graph[t]) if(!seen[ch]) {
			dads[ch].push_back(t);
			tree[t].push_back(ch);
			bfs.push_back(ch);
		}
	}

	vector<int> depths(n, 0);
	for(int i = 1; i < n; ++i) {
		int node = ord[i];
		depths[node] = depths[dads[node][0]] + 1;
	};

	// int levels = 0;
	// for(int i = 1; i < n; i <<= 1) levels++;
	int levels = 20;
	for(int l = 1; l < levels; ++l) {
		for(int i = 0; i < n; ++i) {
			dads[i].emplace_back();
			dads[i][l] = dads[dads[i][l-1]][l-1];
		}
	}

	function<int(int, int)> lca = [&](int a, int b) {
		if(depths[a] > depths[b]) swap(a, b);
		for(int l = levels-1; l >= 0; --l)
			if(depths[b] - depths[a] >= (1 << l))
				b = dads[b][l];
		assert(depths[a] == depths[b]);
		for(int l = levels-1; l >= 0; --l) {
			if(dads[b][l] != dads[a][l]) {
				a = dads[a][l];
				b = dads[b][l];
			}
		}
		assert(dads[a][0] == dads[b][0]);
		// cerr << a << " " << b;
		if(a != b) return dads[a][0]; else return a;
	};

	vector<int> res(n, 0);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		res[a]++;
		res[b]++;
		int l = lca(a, b);
		res[l]--;
		if(l != 0) res[dads[l][0]]--;
	}

	for(int i = n-1; i >= 0; --i) {
		int node = ord[i];
		for(int ch : tree[node]) {
			res[node] += res[ch];
		}
	}

	for(int i : res) cout << i << " ";
	cout << "\n";
}
