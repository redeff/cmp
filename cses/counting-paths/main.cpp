#include <bits/stdc++.h>
using namespace std;

typedef set<int> us;

us *join(us *a, us *b) {
	if(a->size() < b->size()) swap(a, b);
	for(int i : *b) {
		if(a->count(i)) a->erase(i);
		else a->insert(i);
	}
	return a;
}

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
	function<void(int, int)> dfs1 = [&](int node, int dad) {
		for(int ch : graph[node]) if(ch != dad) {
			tree[node].push_back(ch);
			dfs1(ch, node);
		}
	};
	dfs1(0, -1);

	vector<us> borders(n);
	vector<int> res(n, 0);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if(a == b) res[a]++;
		else {
			borders[a].insert(i);
			borders[b].insert(i);
		}
	}

	function<us*(int)> dfs2 = [&](int node) {
		us *to = &borders[node];
		int total = to->size();
		for(int ch : tree[node]) {
			us *u = dfs2(ch);
			total += u->size();
			to = join(to, u);
		}
		// assert((total + to->size()) % 2 == 0);
		res[node] += (total + to->size()) / 2;
		return to;
	};
	dfs2(0);

	for(int i : res) cout << i << " ";
	cout << "\n";
}
