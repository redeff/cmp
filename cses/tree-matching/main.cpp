#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<int>> graph(n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a-1].push_back(b-1);
		graph[b-1].push_back(a-1);
	}

	int total = 0;
	function<bool(int, int)> dfs = [&](int node, int dad) {
		bool mat = false;
		for(int ch : graph[node]) if(ch != dad) {
			if(!dfs(ch, node)) mat = true;
		}

		if(mat) total++;
		return mat;
	};

	dfs(0, 0);

	cout << total << endl;

}
