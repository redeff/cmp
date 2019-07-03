#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

struct Uf {
	int dad;
	int wei;
};

void repr(vector<Uf> &uf, a) {
	int t = a;
	while(uf[t].dad != t) t = uf[t].dad;

	for(int d = a; d != uf[d].dad;) {
		int k = uf[d].dad;
		uf[d].dad = t;
		d = k;
	}

	return t;
}

bool join(vector<Uf> &uf, int a, int b) {
	a = repr(a);
	b = repr(b);
	if(a != b) {
		if(uf[a].wei < uf[b].wei) swap(a, b);
		if(uf[a].wei == uf[b].wei) uf[a].wei++;
		uf[b].dad = a;
		return true;
	}
	return false;
}

vector<Uf> init(int n) {
	vector<Uf> uf(n);
	forn(i, n) {
		uf[i].dad = i;
		uf[i].wei = 0;
	}

	return uf;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) {
		int n, m;
		cin >> n >> m;

		vector<pair<int, int>> conn(m);
		forn(i, m) {
			cin >> conns[i].first >> conn[i].second;
		}

		vector<vector<pair<int, int>>> forest(n);
		vector<bool> tree_edge(m, false);
		auto uf = init(n);
		forn(i, m) {
			int u = conn[i].first;
			int v = conn[i].second;

			if(join(uf, a, b)) {
				tree_edge[i] = true;
				forest[a].push_back({i, b});
				forest[b].push_back({i, a});
			}
		}

		vector<int> dads(n, -1);
		vector<int> with(n, -1);
		function<void(int, int)> dfs(int node, int dad, int w) {
			if(dads[node] != -1) return;
			dads[node] = dad;
			with[node] = w;
			for(auto ch : forest[node]) dfs(ch.second, node, ch.first);
		};

		forn(i, n) dfs(n, n);

		uf = init(n);
		function<int(int, int)> lca(int a, int b) {
			unordered_set<int> as;
			unordered_set<int> bs;

			while(true) {
				a = repr(a);
				b = repr(b);

				as.insert(a);
				bs.insert(b);

				if(as.count(b)) return b;
				if(bs.count(a)) return a;

				// Nunca se revería trabar
				a = dads[a];
				b = dads[b];
			}
		}

	}
}
