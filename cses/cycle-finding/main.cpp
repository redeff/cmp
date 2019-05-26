#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Conn {
	int to;
	ll wei;
	bool neg = false;
};

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<Conn>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--; b--;
		graph[a].push_back(Conn {b, c});
	}

	vector<ll> dist(n, 0);
	// vector<Conn> used
	for(int t = 0; t < n; ++t) {
		for(int i = 0; i < n; ++i) {
			for(Conn c : graph[i]) {
				dist[c.to] = min(dist[c.to], dist[i] + c.wei);
			}
		}
	}

	bool cycle = false;
	for(int t = 0; t < n; ++t) {
		// for(int i : dist) cout << i << " ";
		// cout << endl;
		auto old = dist;
		auto prv = vector<ll>(n, 1);
		for(int i = 0; i < n; ++i) {
			for(Conn &c : graph[i]) {
				if(dist[c.to] > dist[i] + c.wei) {
					dist[c.to] = min(dist[c.to], dist[i] + c.wei);
					prv[c.to] = dist[c.to];
				}
			}
		}

		for(int i = 0; i < n; ++i) {
			for(Conn &c : graph[i]) {
				if(prv[c.to] == old[i] + c.wei) {
					cycle = true;
					c.neg = true;
				}
			}
		}
	}

	if(!cycle) {
		cout << "NO" << endl;
		return 0;
	}

	vector<int> color(n, 0);
	vector<int> cyc;
	function<bool(int)> dfs = [&](int node) {
		if(color[node] == 2) return false;
		if(color[node] == 1) {
			cyc.push_back(node);
			return true;
		}
		color[node] = 1;
		for(Conn c : graph[node]) if(c.neg && dfs(c.to)) {
			cyc.push_back(node);
			return true;
		}
		color[node] = 2;
		return false;
	};

	for(int i = 0; i < n; ++i) {
		if(dfs(i)) break;
	}

	cout << "YES" << endl;
	reverse(cyc.begin(), cyc.end());
	for(int i : cyc) cout << i+1 << " ";
	cout << endl;
}
