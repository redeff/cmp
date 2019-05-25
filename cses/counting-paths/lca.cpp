#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;

	constexpr int levels = 20;
	constexpr int bound = 200000;

	static vector<int> graph[bound];
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	static int dads[levels][bound];
	// for(int i = 0; i < levels; ++i) dads[i] = vector<int>(n);

	static int ord[bound];
	static bool seen[bound] = {};
	vector<int> bfs = {0};
	// dads[0].push_back(0);
	dads[0][0] = 0;

	int ind = 0;
	while(!bfs.empty()) {
		int t = bfs.back();
		bfs.pop_back();
		if(seen[t]) continue;
		seen[t] = true;
		ord[ind++] = t;
		for(int ch : graph[t]) if(!seen[ch]) {
			dads[0][ch] = t;
			bfs.push_back(ch);
		}
	}

	static int depths[bound] = {};
	for(int i = 1; i < n; ++i) {
		int node = ord[i];
		depths[node] = depths[dads[0][node]] + 1;
	};

	// int levels = 0;
	// for(int i = 1; i < n; i <<= 1) levels++;
	for(int l = 1; l < levels; ++l) {
		for(int i = 0; i < n; ++i) {
			dads[l][i] = dads[l-1][dads[l-1][i]];
		}
	}

	function<int(int, int)> lca = [&](int a, int b) {
		if(depths[a] > depths[b]) swap(a, b);
		for(int l = levels-1; l >= 0; --l)
			if(depths[b] - depths[a] >= (1 << l))
				b = dads[l][b];
		assert(depths[a] == depths[b]);
		for(int l = levels-1; l >= 0; --l) {
			if(dads[l][b] != dads[l][a]) {
				a = dads[l][a];
				b = dads[l][b];
			}
		}
		assert(dads[0][a] == dads[0][a]);
		// cerr << a << " " << b;
		if(a != b) return dads[0][a]; else return a;
	};

	static int res[bound] = {};
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		res[a]++;
		res[b]++;
		int l = lca(a, b);
		res[l]--;
		if(l != 0) res[dads[0][l]]--;
	}

	for(int i = n-1; i > 0; --i) {
		int node = ord[i];
		res[dads[0][node]] += res[node];
	}

	for(int i = 0; i < n; ++i) cout << res[i] << " ";
	cout << "\n";
}
