// Accepted
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

struct Union_Find {
	struct Union_Find_Element {
		int dad;
		int wei;
		// int upp;
		// int size;
	};

	vector<Union_Find_Element> data;

	Union_Find(int n) : data(n) {
		forn(i, n) {
			data[i].dad = i;
			// data[i].size = 1;
			// data[i].upp = i;
			data[i].wei = 0;
		}
	}

	int repr(int node) {
		int t = node;
		while(data[t].dad != t) t = data[t].dad;

		while(data[node].dad != node) {
			int k = data[node].dad;
			data[node].dad = t;
			node = k;
		}

		return t;
	}

	bool join(int a, int b) {
		a = repr(a);
		b = repr(b);

		if(a != b) {
			if(data[a].wei < data[b].wei) swap(a, b);
			else if(data[a].wei == data[b].wei) data[a].wei++;
			/*
			if(depths[data[a].upp] > depths[data[b].upp]) {
				data[a].upp = data[b].upp;
			}
			*/
			// data[a].size += data[b].size;
			data[b].dad = a;
			return true;
		}

		return false;
	}
};

struct Forest {
	Union_Find nodes;

	struct Tree {
		int size;
		int root;
	};

	vector<int> my_tree;
	vector<int> depths;
	vector<Tree> trees;
	vector<int> dads;
	vector<int> bests;

	int total;

	vector<vector<int>> tree;

	Forest(int n) :
		my_tree(n),
		trees(n),
		nodes(n),
		depths(n),
		tree(n),
		dads(n),
		bests(n) {

		total = 0;
		forn(i, n) {
			my_tree[i] = i;
			trees[i] = Tree {1, i};
			depths[i] = 0;
			dads[i] = i;
			bests[i] = i;
		}
	}

	int edge(int u, int v) {
		// u = nodes.repr(u);
		// v = nodes.repr(v);

		if(my_tree[u] != my_tree[v]) {
			tree[u].push_back(v);
			tree[v].push_back(u);
			total++;
			if(trees[my_tree[u]].size < trees[my_tree[v]].size) {
				swap(u, v);
			}

			trees[my_tree[u]].size += trees[my_tree[v]].size;

			function<void(bool, int, int, int, int)> dfs =
				[&](bool n, int node, int dad, int depth, int truedad) {
					bests[nodes.repr(node)] = node;
					dads[node] = truedad;
					assert(nodes.repr(node) != nodes.repr(truedad));
					my_tree[node] = my_tree[u];
					depths[node] = depth;
					for(int ch : tree[node]) if(ch != dad) {
						if(nodes.repr(ch) != nodes.repr(node))
							dfs(true, ch, node, depth+1, node);
						else dfs(false, ch, node, depth+1, truedad);
					}
				};

			dfs(true, v, u, depths[u]+1, u);
		}

		else {
			// cerr << "INNODE " << u << " " << v << endl;
			// u = nodes.data[nodes.repr(u)].upp;
			// v = nodes.data[nodes.repr(v)].upp;
			u = nodes.repr(u);
			v = nodes.repr(v);
			int dad = dads[v];
			while(u != v) {
				if(depths[bests[u]] >= depths[bests[v]]) {
					total--;
					int t = nodes.repr(dads[u]);
					dad = dads[t];
					bests[u] = bests[t];
					nodes.join(t, u);
					u = nodes.repr(u);
					dads[u] = nodes.repr(dad);
					v = nodes.repr(v);
				}

				swap(u, v);
			}

			dads[u] = nodes.repr(dad);
		}

		return total;
	}
};

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int t;
	cin >> t;
	while(t --> 0) {
		int n, m;
		cin >> n >> m;
		Forest f(n);
		while(m --> 0) {
			int u, v;
			cin >> u >> v;
			cout << f.edge(u, v) << "\n";
		}
	}
}
