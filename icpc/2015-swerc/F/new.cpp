#include <bits/stdc++.h>
using namespace std;

vector<int> tree;
char n;

typedef unsigned int uint;

uint expand(uint a) {
	uint res = 0;
	for(char x = 0; x < n; ++x) {
		if((tree[x] & a) != 0) res |= 1 << x;
	}
	return res;
}

uint expand_at(uint a, char x) {
	a &= ~(1u << x);
	return expand(a);
}

int main() {
	int tmp, m;
	while(cin >> tmp >> m && tmp != 0) {
		n = (char) tmp;
		tree = vector<int>(n, 0);
		for(int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			tree[a] |= 1 << b;
			tree[b] |= 1 << a;
		}

		vector<char> dp(1 << n, n+1);
		vector<uint> len(1 << n, 1 << n);

		len[0] = 0;

		vector<uint> bfs = {};
		while(!bfs.empty()) {
			vector<uint> nbfs;
			for(uint node : bfs) {
				if(len[node] != (1u << n)) return;
				len[node] = 1 + (1u << n);
				for(char x = 0; x < n; ++x) if((1 << x) & node) {
					uint r = expand_at(node, x);
					dfs(r);
					if(len[r] + 1 < len[node]) {
					// if(len[r] + 1 < (1 << n)) {
						dp[node] = x;
						len[node] = len[r] + 1;
					}
				}
			}
		}
		function<void(uint)> dfs = [&](uint node) {
			if(len[node] != (1u << n)) return;
			// cout << bitset<5>(node) << endl;
			len[node] = 1 + (1u << n);
			
		};

		// cerr << bitset<4>(expand_at(3, 0)) << endl;

		uint i = (1 << n) - 1;
		dfs(i);
		if(len[i] == 1 + (1u << n)) {
			cout << "Impossible" << endl;
			continue;
		}
		int tot = (1 << n) + 10;
		vector<char> res;
		while(i != 0 && tot --> 0) {
			// cout << bitset<22>(i) << " " << (int)dp[i] << endl;
			res.push_back(dp[i]);
			i = expand_at(i, dp[i]);
			/*
			if(dp[i] == n+1) {
				break;
				cout << "Impossible" << endl;
			}
			*/
		}
		cout << res.size() << ":";
		// reverse(res.begin(), res.end());
		for(char c : res) cout << " " << (int)c;
		cout << endl;
	}
}
