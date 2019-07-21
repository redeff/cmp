#include <bits/stdc++.h>
using namespace std;

struct Conn {
	int index;
	int to;
};

struct Bi_Conn {
	int from;
	int to;
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<Conn>> graph(n);
	vector<Bi_Conn> edges(m);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		edges[i].from = a;
		edges[i].to = b;
		graph[b].emplace_back(i, a);
		graph[a].emplace_back(i, b);
	}

	vector<int> depths(n, -1);
	vector<bool> articulation(n);
	// vector<bool> bridge(m, false);
	function<int(int, int, int)> dfs1 = [&](int root, int node, int depth) {
		assert(depths[node] == -1);
		depths[node] = depth;

		int far = depth;
		int farchild = 0;
		int deg = 0;
		for(Conn ch : graph[node]) {
			if(seen[ch.to]) {
				far = min(far, depths[ch.to]);
			}
			else {
				deg++;
				int f = dfs(root, ch.to, depth+1);
				farchild = max(f, farchild);
				far = min(f, far);
			}
		}

		if(node == root) {
			articulation[node] = deg > 1;
		} else {
			articulation[node] = (farchild >= depth && deg != 0);
		}
		return far;
	};

	for(int i = 0; i < n; ++i) {
		if(depths[i] == -1) {
			dfs1(i);
		}
	}

	vector<int> color(n+m, -1);
	for(int i = 0; i < n; ++i) if(articulation[i]) color[i] = i;

	vector<vector<int>> tree(n+m);
	function<void(int, int)> dfs2 = [&](int node, int col) {
		if(articulation[node]) {
			tree[node].push_back(col);
			tree[col].push_back(node);
		} else {
			if(col[node] != -1) return;
			col[node] = col;
			for(Conn ch : graph[node]) {
				col[n + ch.index] = col;
				dfs2(ch.to, col);
			}
		}
	};

	for(int i = 0; i < m; ++i) {
		if(color[n+i] == -1) {
			color[n+i] = n+i;
			dfs2(edges[n+i].to, n+i);
			dfs2(edges[n+i].from, n+i);
		}
	}

	vector<vector<int>> dads(n+m, 0);
	vector<int> comp(n+m, -1);
	vector<int> lca_depth(n+m, 0);
	function<void(int, int, int, int)> dfs3 = [&](int node, int dad, int col, int depth) {
		if(comp[node] != -1) return;
		lca_depth[node] = depth;

		comp[node] = col;
		dads[node].push_back(dad);

		for(int ch : tree[node]) dfs3(ch, node, col, depth+1);
	}

	for(int i = 0; i < n+m; ++i) {
		if(comp[i] == -1) dfs3(i, i, i);
	}

	const int BOUND = 20;
	for(int l = 0; l < BOUND; ++l) {
		for(int i = 0; i < n+m; ++i) {
			dads[i].push_back(dads[dads[i][l]][l]);
		}
	}

	auto goto_depth = [&](int a, int d) {
		for(int l = BOUND; l >= 0; --l) {
			if(lca_depth[dads[a][l]] >= d) a = dads[a][l];
		}

		return a;
	};

	auto blocks = [&](int a, int b, int c) {
		if(comp[a] == comp[b] && comp[b] == comp[b]) {
			// if(color[a] == color[c]) return false;
			if(a == c || b == c) return true;
			if(!articulation[b]) return false;
			int aa = goto_depth(a, lca_depth[c]-1);
			int bb = goto_depth(b, lca_depth[c]-1);
			if(dads[aa][0] != c && dads[bb][0] != c) return false;
			if(aa == bb) return false;
			return true;
		} else {
			return true;
		}
	}

	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		int t;
		int a, b, c;
		cin >> t >> a >> b >> c;
		bool ans;
		if(t == 1) {
			int d;
			cin >> d;
			ans = blocks(a, b, c) && blocks(a, b, d);
		} else {
			ans = blocks(a, b, c);
		}

		if(ans) cout << "da" << endl;
		else cout << "ne" << endl;
	}
}
