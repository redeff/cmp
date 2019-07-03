#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

struct Uf {
	struct UfElement {
		int dad;
		int wei;
	};

	vector<UfElement> data;

	Uf(int n) {
		data = vector<UfElement>(n);
		forn(i, n) {
			data[i].dad = i;
			data[i].wei = 0;
		}
	}

	int repr(int a) {
		int t = a;
		while(data[t].dad != t) t = data[t].dad;

		while(data[a].dad != a) {
			int k = data[a].dad;
			data[a].dad = t;
			a = k;
		}

		return t;
	}

	bool join(int a, int b) {
		a = repr(a);
		b = repr(b);
		if(a == b) return false;

		if(data[a].wei < data[b].wei) swap(a, b);
		if(data[a].wei == data[b].wei) data[a].wei++;
		data[b].dad = a;

		return true;
	}
};

struct Conn {
	int to;
	int index;
};

struct BiConn {
	int u;
	int v;
};

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int testcases;
	cin >> testcases;
	while(testcases --> 0) {
		int n, m;
		cin >> n >> m;

		vector<BiConn> edges(m);
		forn(i, m) cin >> edges[i].u >> edges[i].v;

		Uf conn_comp(n);
		vector<vector<Conn>> forest(n);
		vector<bool> tree_edge(m, false);
		forn(i, m) {
			int u = edges[i].u;
			int v = edges[i].v;
			if(conn_comp.join(u, v)) {
				forest[u].push_back({v, i});
				forest[v].push_back({u, i});
				tree_edge[i] = true;
			}
		}

		vector<Conn> dads(n, {-1, -1});
		vector<int> depths(n);
		function<void(int, Conn, int)> dfs =
			[&](int node, Conn dad, int depth) {
				if(dads[node].to != -1) return;
				dads[node] = dad;
				depths[node] = depth;

				for(Conn ch : forest[node])
					dfs(ch.to, Conn {node, ch.index}, depth+1);
			};

		forn(i, n) dfs(i, Conn {i, -1}, 0);

		Uf bicomp(n);
		vector<int> tim(m);
		auto lca = [&](int a, int b, int times) {
			a = bicomp.repr(a);
			b = bicomp.repr(b);

			// Puedo hacer lineal pq dps los mato a todos
			while(a != b) {
				if(depths[a] >= depths[b]) {
					tim[dads[a].index] = times;
					int t = bicomp.repr(dads[a].to);
					bicomp.join(a, t);
					a = bicomp.repr(a);
				}
				swap(a, b);
			}
		};

		forn(i, m) {
			if(!tree_edge[i]) {
				lca(edges[i].u, edges[i].v, i);
			}
		}

		vector<int> diff(m);
		forn(i, m) {
			if(tree_edge[i]) {
				diff[i]++;
				diff[tim[i]]--;
			}
		}

		forn(i, m-1) {
			diff[i+1] += diff[i];
		}

		for(int i : diff) cout << i << " ";
		cout << "\n";
	}
}
