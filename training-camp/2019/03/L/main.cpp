#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

typedef vector<vector<int>> Graph;

struct Block_Cut_Tree {
	Graph forest;
	vector<int> mapping;
	// vector<bool> art;
	vector<int> relevant;
};

// g es la lista de adyacencia de un grafo en forma vector<int>, N es cantidad de vertices,
// MAXN es una cota superior tanto para cantidad de vertices como cantidad de aristas

/*
vector<vector<int>> _cmps;
vector<bool> _art;
vector<bool> _this_cmp;
void COMPO_START() {
	_cmps.emplace_back();
	// _cmps.emplace_back();
}

void COMPO_EDGE(int a, int b) {
}

void COMPO_V(int v) {
	if(!_this_cmp[v]) {
		// cerr << v+1 << " ";
		_this_cmp[v] = true;
		_cmps.back().push_back(v);
	}
}

void COMPO_END() {
	// cerr << endl;
	// cerr << "---------------------";
	// cerr << endl;
	for(int i : _cmps.back()) _this_cmp[i] = false;
}

void ARTICULATION(int v) {
	_art[v] = true;
}

const int MAXN = 550000;
Graph g;
int N;
int D[MAXN], L[MAXN], J[MAXN], I[MAXN]; char E[MAXN];
int P[2 * MAXN], R, S[2 * MAXN], K, A[MAXN], T;
void component() {
    int r = P[--R]; COMPO_START(); COMPO_V(r);
    for (int u = P[R - 1]; u != r; u = P[--R - 1]) {
        COMPO_V(u);
        // if (D[P[R - 2]] < D[u]) forn(i, J[u]) COMPO_EDGE(u, g[u][i]);
    } COMPO_END();
}
void dfs_agus (int r) {
    E[r] = K = T = R = 0; A[S[K++] = r] = -1;
    while (K) { int u = S[--K], v;
        switch (E[u]) {
        case 0: L[u] = D[u] = T++; J[u] = I[u] = 0; P[R++] = u;
        case 1: c1: if (I[u] == (int)g[u].size()) break;
            if (D[v = g[u][I[u]]] == -1) {
                if(u == r and I[u]) ARTICULATION(u);
                E[A[v] = S[K++] = u] = 2, E[S[K++] = v] = 0;
            } else { if (v != A[u] && D[v] < L[u]) L[u] = D[v];
                if (D[v] < D[u]) swap(g[u][J[u]++], g[u][I[u]]); //COMP
                I[u]++; E[S[K++] = u] = 1;
            } break;
        case 2: v = g[u][I[u]], P[R++] = u;
            if (L[v] < L[u]) L[u] = L[v];
            if (L[v] >= D[u] && u != r) ARTICULATION(u);
            //if (L[v] >= D[v]) BRIDGE(u, v);
            if (L[v] >= D[u]) component(); //COMP
            I[u]++; goto c1;
        }
    }
}

void BC()
{
    forn(i, N) D[i] = -1;
    forn(i, N) if(D[i] == -1) dfs_agus(i);
}
*/

Block_Cut_Tree biconnected_components(Graph &graph) {
	int n = graph.size();

	/*
	N = n;
	g = graph;
	_cmps = vector<vector<int>> {};
	_art = vector<bool>(n, false);
	_this_cmp = vector<bool>(n, false);

	BC();
	*/
 
	vector<int> num(n, 0), low(n, 0), stk;
	vector<bool> art(n, false);
	vector<vector<int>> comps;
 
	function<void(int, int, int&)> dfs = [&](int u, int p, int &t) {
		num[u] = low[u] = ++t;
		stk.push_back(u);
 
		for (int v : graph[u]) if (v != p) {
			if (!num[v]) {
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);
 
				if (low[v] >= num[u]) {
					art[u] = (num[u] > 1 || num[v] > 2);
 
					comps.push_back({u});
					while (comps.back().back() != v)
						comps.back().push_back(stk.back()), stk.pop_back();
				}
			}
			else low[u] = min(low[u], num[v]);
		}
	};
 
	int t = 0;
	dfs(0, -1, t);
	// for(int i = 0; i < n; ++i) assert(num[i]);
	// for(int i = 0; i < n; ++i) assert(low[i]);
	for(int i = 0; i < n; ++i) if(graph[i].size() == 1) art[i] = true;

	// vector<vector<int>> comps = _cmps;
	// vector<bool> art = _art;
 
	Graph tree;
	vector<int> id(n);
	vector<int> relevant;

	for (int u = 0; u < n; ++u) {
		if (art[u]) {
			// cerr << u << "is "  << endl;
			id[u] = tree.size();
			relevant.push_back(2);
			tree.emplace_back();
		}
		// cerr << u << "no "  << endl;
	}

	for (auto &comp : comps) {
		int node = tree.size();
		tree.emplace_back();
		relevant.push_back((comp.size() == 2) ? 1 : 0);
		// assert(!comp.empty());
		for (int u : comp) {
			// // cerr << u << " ";
			if (!art[u]) id[u] = node;
			else {
				tree[node].push_back(id[u]);
				tree[id[u]].push_back(node);
			}
		}
		// cerr << endl;
	}

	// cerr << "size: " << comps.size() << endl;
	// cerr << "size: " << tree.size() << endl;
	return Block_Cut_Tree {
		tree,
		id,
		// art,
		relevant
	};
}

struct Query {
	int node;
	int depth;
};

vector<int> batch_queries(Graph forest, vector<Query> qs) {
	int n = forest.size();
	int m = qs.size();
	vector<int> out(m, -1);
	
	vector<vector<Query>> ata(n);
	for(int i = 0; i < m; ++i) {
		ata[qs[i].node].push_back(Query {i, qs[i].depth});
	}

	vector<int> nodes;
	vector<bool> seen(n, false);
	function<void(int)> dfs = [&](int node) {
		if(seen[node]) return;
		seen[node] = true;
		nodes.push_back(node);
		for(Query q : ata[node]) {
			out[q.node] = nodes[min(q.depth, int(nodes.size())-1)];
		}
		for(int ch : forest[node]) {
			dfs(ch);
		}
		nodes.pop_back();
	};

	dfs(0);
	// for(int i = 0; i < n; ++i) assert(seen[i]);
	// for(int i = 0; i < m; ++i) assert(out[i] != -1);

	return out;
}

pair<vector<int>, vector<int>> depths_and_dads(Graph &graph) {
	int n = graph.size();
	vector<int> depths(n, -1);
	vector<int> dads(n, -1);

	function<void(int, int, int)> dfs = [&](int node, int depth, int dad) {
		assert(depths[node] == -1);
		assert(dads[node] == -1);
		depths[node] = depth;
		dads[node] = dad;
		for(int ch : graph[node]) if(ch != dad) dfs(ch, depth+1, node);
	};

	dfs(0, 0, 0);
	// for(int i = 0; i < n; ++i) {
		// cerr << i << endl;
		// assert(dads[i] != -1);
	// }
	// for(int i = 0; i < n; ++i) assert(depths[i] != -1);

	return {depths, dads};
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	int m;
	cin >> n >> m;

	Graph graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	Block_Cut_Tree bctree = biconnected_components(graph);
	auto p = depths_and_dads(bctree.forest);
	vector<int> depths = p.first;
	vector<int> dads = p.second;

	struct Big_Query {
		int index;
		int x;
		bool failed;
	};

	int q;
	cin >> q;

	/*
	if(n == 2) {
		for(int i = 0; i < q; ++i) {
			cout << "ne" << endl;
		}
		return 0;
	}
	*/

	vector<Big_Query> qs(q);
	vector<Query> batch;
	for(int i = 0; i < q; ++i) {
		int t;
		cin >> t;
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		a = bctree.mapping[a];
		b = bctree.mapping[b];
		c = bctree.mapping[c];

		qs[i].index = batch.size();
		qs[i].failed = false;

		if(t == 2) {
			if(bctree.relevant[c] == 2) {
				qs[i].x = c;
				batch.push_back(Query {a, depths[qs[i].x]+1});
				batch.push_back(Query {b, depths[qs[i].x]+1});
			} else {
				qs[i].failed = true;
			}
		} else if(t == 1) {
			int d;
			cin >> d;
			d--;
			d = bctree.mapping[d];

			if(d != c) {
				if(depths[d] < depths[c]) swap(d, c);
				qs[i].x = dads[d];
				// assert(dads[dads[d]] == c || dads[d] == dads[c]);
				if(bctree.relevant[qs[i].x] == 1) {
					batch.push_back(Query {a, depths[qs[i].x]+1});
					batch.push_back(Query {b, depths[qs[i].x]+1});
				} else {
					qs[i].failed = true;
				}
			} else {
				// cerr << "eq " << c << " " << d << endl;
				qs[i].failed = true;
			}
		}
		// } else assert(false);
	}

	vector<int> ans = batch_queries(bctree.forest, batch);

	auto blocks = [&](int aa, int bb, int c) {
		// if(!bctree.relevant[c]) return false;
		if(dads[aa] != c && dads[bb] != c) return false;
		if(aa == bb) return false;
		return true;
	};

	for(Big_Query qu : qs) {
		bool bl;
		if(qu.failed) {
			bl = false;
			// cerr << "fail" << endl;
		}
		else bl = blocks(ans[qu.index], ans[qu.index+1], qu.x);
		if(bl) cout << "ne" << "\n";
		else cout << "da" << "\n";
	}
}
