#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef long long int ll;
const ll base = 10;
struct bigint {
	vector<ll> ns;
	bigint(){}
	bigint(ll k) {
		ns = vector<ll>(10, 0);
		ns[0] = k;
		forn(i, 9) {
			ns[i+1] += ns[i] / base;
			ns[i] %= base;
		}

		while(!ns.empty() && ns.back() == 0) ns.pop_back();
	}
};

bool operator<(bigint a, bigint b) {
	return a.ns.size() < b.ns.size();
}

void print(bigint n) {
	if(n.ns.empty()) cout << 0;
	else {
		reverse(n.ns.begin(), n.ns.end());
		for(ll i : n.ns) cout << i;
	}
}

bigint operator*(bigint a, bigint b) {
	bigint res;
	res.ns = vector<ll>(a.ns.size() + b.ns.size() + 10, 0);

	forn(i, a.ns.size()) forn(j, b.ns.size()) {
		res.ns[i+j] += a.ns[i] * b.ns[j];
	}

	forn(i, a.ns.size() + b.ns.size()+9) {
		res.ns[i+1] += res.ns[i] / base;
		res.ns[i] %= base;
	}

	while(!res.ns.empty() && res.ns.back() == 0) res.ns.pop_back();
	return res;
}

const int MAXN = 2e6+100;
int N;
vector<vector<int>> g;

multiset<bigint> products;
unordered_set<int> ver;
set<pair<int, int>> edg;
void COMPO_START() {
	ver.clear();
	edg.clear();
}

void COMPO_V(int v) {
	// cerr << v+1 << " ";
	ver.insert(v);
}

void COMPO_EDGE(int u, int v) {
	// cerr << u+1 << "-" << 1+v << " ";
	if(u < v) swap(u, v);
	edg.insert({u,v});
}

// bigint total;
void COMPO_END() {
	// cerr << endl;
	// cerr << ver.size() << " " << edg.size() << endl;
	if(edg.size() > ver.size()) {
		// cerr << "zero" << endl;
		products.insert(bigint(0));
	}
	else if(edg.size() == 1) {
		assert(ver.size() == 2);
	} else {
		assert(ver.size() == edg.size());
		products.insert(bigint(1+edg.size()));
		// total = total*bigint(1+edg.size());
	}
}

int D[MAXN], L[MAXN], J[MAXN], I[MAXN]; char E[MAXN];
int P[2 * MAXN], R, S[2 * MAXN], K, A[MAXN], T;
void component() {
	int r = P[--R]; COMPO_START(); COMPO_V(r);
	for (int u = P[R - 1]; u != r; u = P[--R - 1]) {
		COMPO_V(u);
		if (D[P[R - 2]] < D[u]) forn(i, J[u]) COMPO_EDGE(u, g[u][i]);
	} COMPO_END();
}
void dfs (int r) {
	E[r] = K = T = R = 0; A[S[K++] = r] = -1;
	while (K) { int u = S[--K], v;
		switch (E[u]) {
			case 0: L[u] = D[u] = T++; J[u] = I[u] = 0; P[R++] = u;
			case 1: c1: {
				if (I[u] == (int)g[u].size()) break;
				if (D[v = g[u][I[u]]] == -1) {
					//if(u == r and I[u]) ARTICULATION(u);
					E[A[v] = S[K++] = u] = 2, E[S[K++] = v] = 0;
				} else { if (v != A[u] && D[v] < L[u]) L[u] = D[v];
					if (D[v] < D[u]) swap(g[u][J[u]++], g[u][I[u]]); //COMP
					I[u]++; E[S[K++] = u] = 1;
				} break;
			}
			case 2: {
				v = g[u][I[u]], P[R++] = u;
				if (L[v] < L[u]) L[u] = L[v];
				//if (L[v] >= D[u] && u != r) ARTICULATION(u);
				//if (L[v] >= D[v]) BRIDGE(u, v);
				if (L[v] >= D[u]) component(); //COMP
				I[u]++; goto c1;
			}
		}
	}
}
void BC()
{
	forn(i, N) D[i] = -1;
	forn(i, N) {
		if(D[i] == -1) {
			if(i > 0) {
				products.insert(bigint(0));
			}
			dfs(i);
		}
	}
}
int main() {
	int n, m;
	bool fst = true;
	while(cin >> n >> m) {
		if(!fst) cout << endl;
		fst = false;
		N = n;
		g = vector<vector<int>>(n);
		forn(akjsdhfa, m) {
			int k;
			cin >> k;
			int last = -1;
			forn(kjsahfak, k) {
				int t;
				cin >> t;
				--t;
				if(last != -1) {
					g[t].push_back(last);
					g[last].push_back(t);
				}
				last = t;
			}
		}

		BC();
		products.insert(bigint(1));
		/*
		for(bigint i : products) {
			print(i);
			cerr << " ";
		}
		*/
		// cerr << endl;
		while(products.size() != 1) {
			auto it = products.begin();
			bigint a = *it;
			products.erase(it);
			it = products.begin();
			bigint b = *it;
			products.erase(it);

			products.insert(a*b);
		}
		print(*products.begin());
		products.clear();
		cout << endl;
	}
}
