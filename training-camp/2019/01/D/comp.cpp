#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;
const int MAXN = 100010;

vector<vector<int>> g;

vector<int> verts;
// vector<pair<int, int>> edges;
void COMPO_START() {
	verts.clear();
	// edges.clear();
}

vector<int> sub[MAXN];
void COMPO_EDGE(int a, int b) {
	sub[a].push_back(b);
	sub[b].push_back(a);
	// edges.push_back({a, b});
}

void COMPO_V(int a) {
	verts.push_back(a);
}
bool res[MAXN];
bool color[MAXN];


void COMPO_END() {
	// sort(verts.begin(), verts.end());

	for(int i : verts) {
		color[i] = 0;
	}
	// vector<vector<int>> sub(verts.size());

	color[verts[0]] = 1;
	vector<int> bag;
	bag.push_back(verts[0]);
	while(!bag.empty()) {
		int node = bag.back();
		bag.pop_back();
		for(int ch : sub[node]) {
			if(color[ch] == 0) {
				color[ch] = -color[node];
				bag.push_back(ch);
			} else if(color[ch] == color[node]) {
				for(auto i : verts) res[i] = true;
				return;
			}
		}
	}

	forn(i, 100) sub[i].clear();
	for(int i : verts) {
		sub[i].clear();
	}
}

// g es la lista de adyacencia de un grafo en forma vector<int>, N es cantidad de vertices,
// MAXN es una cota superior tanto para cantidad de vertices como cantidad de aristas

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
        case 1: c1: if (I[u] == (int)g[u].size()) break;
            if (D[v = g[u][I[u]]] == -1) {
                //if(u == r and I[u]) ARTICULATION(u);
                E[A[v] = S[K++] = u] = 2, E[S[K++] = v] = 0;
            } else { if (v != A[u] && D[v] < L[u]) L[u] = D[v];
                if (D[v] < D[u]) swap(g[u][J[u]++], g[u][I[u]]); //COMP
                I[u]++; E[S[K++] = u] = 1;
            } break;
        case 2: v = g[u][I[u]], P[R++] = u;
            if (L[v] < L[u]) L[u] = L[v];
            //if (L[v] >= D[u] && u != r) ARTICULATION(u);
            //if (L[v] >= D[v]) BRIDGE(u, v);
            if (L[v] >= D[u]) component(); //COMP
            I[u]++; goto c1;
        }
    }
}

int N;
void BC()
{
    forn(i, N) D[i] = -1;
    forn(i, N) if(D[i] == -1) dfs(i);
}

void caso() {
	int n, m;
	cin >> n >> m;
	N = n;
	// vector<vector<int>> graph(n);
	g = vector<vector<int>>(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		// cerr << a << " " << b << endl;
		--a; --b;
		// cerr << a << " " << b << endl;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	for(int i = 0; i < n; ++i) res[i] = false;
	BC();
	int total = 0;
	for(int i = 0; i < n; ++i) if(res[i]) total++;
	cout << total << "\n";
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int test;
	cin >> test;
	while(test --> 0) caso();
}
