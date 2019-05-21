#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll ft_get(vector<ll> &ft, int node) {
	node += 10;
	ll res = 0;
	for(int x = node; x; x -= x & -x) {
		res += ft[x];
	}
	return res;
}

void ft_set(vector<ll> &ft, int node, ll delta) {
	node += 10;
	for(int x = node; x < ft.size(); x += x & -x) {
		ft[x] += delta;
	}
}

struct Node {
	int decom_par;
	int mapping;
	int dad;
	int size;
	int best_child;
};

int main() {
	int n, q;
	cin >> n >> q;

	vector<vector<int>> graph(n);
	vector<ll> vals(n);
	for(ll &i : vals) cin >> i;
	
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<Node> tree(n);

	// vector<bool> seen(n, false);
	function<void(int)> dfs1 = [&](int node) {
		// tree[node].dad = dad;
		tree[node].size = 1;
		tree[node].best_child = -1;
		int biggest = -1;
		for(int ch : graph[node]) if(ch != tree[node].dad) {
			tree[ch].dad = node;
			dfs1(ch);
			if(tree[ch].size > biggest) {
				biggest = tree[ch].size;
				tree[node].best_child = ch;
			}
			tree[node].size += tree[ch].size;
		}
	};

	tree[0].dad = -1;
	dfs1(0);

	vector<ll> ft(n + 30, 0);

	function<void(int, int&, int)> dfs2 = [&](int node, int &mapping, int dad) {
		tree[node].mapping = mapping;
		tree[node].decom_par = dad;
		mapping++;
		if(tree[node].best_child != -1) dfs2(tree[node].best_child, mapping, dad);
		for(int ch : graph[node]) if(ch != tree[node].dad && ch != tree[node].best_child) {
			dfs2(ch, mapping, ch);
		}
	};

	int mapping = 0;
	dfs2(0, mapping, 0);

	function<ll(int)> sum = [&](int node) {
		if(node == -1) return 0ll;
		int dad = tree[node].decom_par;
		return ft_get(ft, tree[node].mapping) - ft_get(ft, tree[dad].mapping - 1) + sum(tree[dad].dad);
	};

	function<void(int, ll)> sett = [&](int node, ll val) {
		if(node == -1) return;
		ft_set(ft, tree[node].mapping, val - vals[node]);
		vals[node] = val;
	};

	for(int i = 0; i < n; ++i) {
		ll val = vals[i];
		vals[i] = 0;
		sett(i, val);
		// vals[i] = i;
	}

	for(int j = 0; j < q; ++j) {
		int t, i;
		ll x;
		cin >> t >> i;
		if(t == 2) cout << sum(i - 1) << endl;
		else {
			cin >> x;
			sett(i-1, x);
		}
	}
}
