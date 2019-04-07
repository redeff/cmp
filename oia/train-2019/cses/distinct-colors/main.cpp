#include <bits/stdc++.h>
using namespace std;

typedef unordered_set<int> st;

void mer(st &a, st &&b) {
	if(a.size() < b.size()) swap(a, b);
	for(auto x : b) a.insert(x);
}

int main() {
	int n;
	cin >> n;

	vector<int> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];

	vector<vector<int>> tree(n);
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	vector<int> res(n);
	function<st(int, int)> dfs = [&](int node, int dad) {
		st subtree;
		for(int ch : tree[node]) if(ch != dad) mer(subtree, dfs(ch, node));
		subtree.insert(ns[node]);
		res[node] = subtree.size();
		return subtree;
	};

	dfs(0, -1);

	for(int r: res) cout << r << " ";
	cout << endl;
}
