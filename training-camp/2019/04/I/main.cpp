#include <bits/stdc++.h>
using namespace std;

int mod = 'z' - 'a' + 1;

int main() {
	string s;
	cin >> s;
	int n = s.size();

	int m;
	cin >> m;
	vector<vector<int>> graph(n/2 + 1);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		a = min(a, n-a);
		b = min(b, n-b);
		if(a != b) {
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
	}

	vector<int> vec(n/2);
	for(int i = 0; i < n/2; ++i) {
		vec[i] = int(s[i]) - int(s[n-1-i]);
		vec[i] %= mod;
		vec[i] += mod;
		vec[i] %= mod;
	}

	n  = n/2+1;

	vector<bool> seen(n, false);
	function<void(int, vector<int>&)> dfs = [&](int node, vector<int> &comp) {
		if(seen[node]) return;
		seen[node] = true;
		comp.push_back(node);
		for(int ch : graph[node]) dfs(ch, comp);
	};

	vector<int> finish(n, -1);
	vector<int> start(n, -1);
	vector<int> total;
	for(int i = 0; i < n; ++i) {
		if(!seen[i]) {
			vector<int> comp;
			dfs(i, comp);
			sort(comp.begin(), comp.end());
			for(int j = 1; j < comp.size(); ++j) {
				start[comp[j-1]] = total.size();
				finish[comp[j]] = total.size();
				total.push_back(0);
			}
		}
	}

	int sum = 0;
	bool can = true;
	for(int i = 0; i < n-1; ++i) {
		assert(vec[i] >= 0);
		assert(sum >= 0);
		vec[i] += sum;
		vec[i] %= mod;
		if(vec[i] != 0) {
			if(start[i] == -1) can = false;
			else {
				sum += mod - vec[i];
				sum %= mod;
				total[start[i]] = (mod - vec[i]) % mod;
			}
		}
		if(finish[i+1] != -1) {
			sum += mod - total[finish[i+1]];
			sum %= mod;
		}
	}

	if(can) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
