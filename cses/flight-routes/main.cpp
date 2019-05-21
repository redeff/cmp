#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Conn {
	int to;
	ll wei;
};

bool operator<(Conn a, Conn b) {
	return a.wei > b.wei;
}

int k = -1;

vector<vector<ll>> djk(vector<vector<Conn>> &graph, int root) {
	vector<vector<ll>> dist(graph.size());
	priority_queue<Conn> dp;
	dp.push(Conn {root, 0});

	while(!dp.empty()) {
		Conn t = dp.top();
		dp.pop();
		if(dist[t.to].size() >= k && dist[t.to].back() <= t.wei) continue;
		else {
			dist[t.to].push_back(t.wei);
			sort(dist[t.to].begin(), dist[t.to].end());
			if(dist[t.to].size() > k) dist[t.to].pop_back();
		}

		for(Conn c : graph[t.to]) {
			dp.push(Conn {c.to, c.wei + t.wei});
		}
	}

	return dist;
}

int main() {
	int n, m;
	cin >> n >> m >> k;
	vector<vector<Conn>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--;
		b--;
		graph[a].push_back(Conn {b, c});
	}

	vector<vector<ll>> res = djk(graph, 0);
	for(ll d : res[n-1]) cout << d << " ";
	cout << endl;
}
