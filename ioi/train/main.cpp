#include<bits/stdc++.h>
using namespace std;

int flog(int a) {
	return 8 * (sizeof (int)) - __builtin_clz(a) - 1;
}
struct Node {
	int dad;
	vector<int> ch;
	int depth;
};

vector<Node> create(int n, vector<pair<int, int>> &conn) {
	vector<vector<int>> tree(n);
	for(auto p: conn) {
		tree[p.first].push_back(p.second);
		tree[p.second].push_back(p.first);
	}

	vector<Node> rtree(n);
	vector<bool> visited(n, false);
	function<void(int, int)> root = [&](int node, int depth) {
		visited[node] = true;
		rtree[node].depth = depth;
		for(int ch: tree[node]) {
			if(!visited[ch]) {
				rtree[node].ch.push_back(ch);
				root(ch, depth + 1);
			} else {
				rtree[node].dad = ch;
			}
		}
	};

	root(0, 0);
	rtree[0].dad = 0;
	return rtree;
}

struct SparseNode {
	int depth;
	vector<int> ans;
};

vector<SparseNode> sparse(int ln, int n, vector<Node> &rtree) {
	vector<SparseNode> stree(n);
	for(int i = 0; i < n; ++i) {
		stree[i].depth = rtree[i].depth;
		stree[i].ans = vector<int>(ln);
		stree[i].ans[0] = rtree[i].dad;
	}
	for(int k = 1; k < ln; ++k) {
		for(int i = 0; i < n; ++i) {
			stree[i].ans[k] = stree[stree[i].ans[k-1]].ans[k-1];
		}
	}

	return stree;
}

int lca(int a, int b, vector<SparseNode> &stree) {
	if(stree[a].depth > stree[b].depth) swap(a, b);
	while(stree[a].depth < stree[b].depth) {
		b = stree[b].ans[flog(stree[b].depth - stree[a].depth)];
	}
	if(a == b) return a;
	for(int k = stree[a].ans.size() - 1; k >= 0; --k) {
		if(stree[a].ans[k] != stree[b].ans[k]) {
			a = stree[a].ans[k];
			b = stree[b].ans[k];
		}
	}

	return stree[a].ans[0];
}


int main() {
	int n;
	cin >> n;

	vector<pair<int, int>> conn(n-1);
	for(int i = 0; i < n-1; ++i) {
		cin >> conn[i].first >> conn[i].second;
		conn[i].first--;
		conn[i].second--;
	}

	auto rtree = create(n, conn);
	auto stree = sparse(flog(n) + 5, n, rtree);
	
	int k;
	cin >> k;
	vector<int> vals(n, 0);
	for(int i = 0; i < k; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		vals[lca(a, b, stree)] += -2;
		vals[a] += 1;
		vals[b] += 1;
	}

	vector<int> sum(n, 0);
	function<void(int)> calc = [&](int node) {
		sum[node] = vals[node];
		for(int ch : rtree[node].ch) {
			calc(ch);
			sum[node] += sum[ch];
		}
	};
	calc(0);

	for(int i = 0; i < n - 1; ++i) {
		int a = conn[i].first;
		int b = conn[i].second;
		if(stree[a].depth < stree[b].depth) swap(a, b);
		cout << sum[a] << " ";
	}
	cout << endl;
}
