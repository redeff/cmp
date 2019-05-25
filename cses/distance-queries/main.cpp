#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> graph(n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	const int levels = 20;
	vector<int> dads[levels];
	for(int i = 0; i < levels; ++i) dads[i] = vector<int>(n);
	dads[0][0] = 0;

	vector<int> depths(n);
	depths[0] = 0;

	vector<int> bag = {0};
	vector<bool> seen(n, false);

	while(!bag.empty()) {
		int i = bag.back(); bag.pop_back();
		seen[i] = true;

		for(int ch : graph[i]) if(!seen[ch]) {
			dads[0][ch] = i;
			depths[ch] = depths[i] + 1;
			bag.push_back(ch);
		}
	}

	for(int l = 1; l < levels; ++l) {
		for(int i = 0; i < n; ++i) {
			dads[l][i] = dads[l-1][dads[l-1][i]];
		}
	}

	auto lca = [&](int a, int b) {
		if(depths[a] > depths[b]) swap(a, b);
		for(int l = levels-1; l >= 0; --l) {
			if(depths[dads[l][b]] >= depths[a]) b = dads[l][b];
		}

		if(a == b) return a;
		for(int l = levels-1; l >= 0; --l) {
			if(dads[l][a] != dads[l][b]) {
				a = dads[l][a];
				b = dads[l][b];
			}
		}
		return dads[0][a];
	};

	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;

		int l = lca(a, b);
		cout << depths[a] + depths[b] - 2 * depths[l] << " ";
		cout << "\n";
	}
}
