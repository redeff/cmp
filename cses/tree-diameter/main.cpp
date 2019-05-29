#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<vector<int>> graph(n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	function<pair<int, int>(int, int)> dfs = [&](int node, int dad) {
		pair<int, int> ans = {-1, node};
		for(int ch : graph[node]) if(ch != dad) {
			ans = max(ans, dfs(ch, node));
		}

		ans.first++;
		return ans;
	};

	auto p = dfs(0, 0);
	cout << dfs(p.second, p.second).first << endl;
}
