#include <bits/stdc++.h>
using namespace std;

int n;
vector<bool> dfs(vector<vector<int>> &gr, int root) {
	vector<bool> seen(n);
	function<void(int)> dfs1 = [&](int node) {
		if(seen[node]) return;
		seen[node] = true;
		for(int ch : gr[node]) dfs1(ch);
	};

	dfs1(root);
	return seen;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int m;
	cin >> n >> m;

	vector<vector<int>> graph(n);
	vector<vector<int>> hparg(n);

	srand(109840198);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		hparg[b].push_back(a);
	}

	vector<int> left;
	for(int i = 0; i < n; ++i) left.push_back(i);
	while(true) {

		// for(int i : left) cout << i << "~";
		// cout << endl;

		int root = rand() % int(left.size());
		// cerr << root << endl;
		vector<bool> as = dfs(graph, root);
		vector<bool> bs = dfs(hparg, root);

		vector<int> nleft;
		for(int i : left) {
			if(as[i] && !bs[i]) nleft.push_back(i);
		}

		if(nleft.empty()) {
			int total = 0;
			for(int i : left) if(as[i]) total++;
			cout << total << "\n";
			for(int i : left) if(as[i]) cout << i+1 << " ";
			cout << "\n";
			return 0;
		} else swap(left, nleft);
	}
}
