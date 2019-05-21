#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll mod = 1e9+7;

struct Conn {
	int to;
	ll wei;
};

bool operator<(Conn a, Conn b) {
	return a.wei > b.wei; // Al revés
}

const ll INF = 33333333333333333ll;
vector<ll> djk(vector<vector<Conn>> &graph, int root) {
	int n = (int) graph.size();
	vector<ll> dist(n, INF);

	priority_queue<Conn> dp;
	dp.push(Conn {root, 0});

	while(!dp.empty()) {
		Conn t = dp.top();
		dp.pop();
		if(dist[t.to] <= t.wei) continue;
		dist[t.to] = t.wei;
		for(Conn c : graph[t.to]) {
			if(c.wei + t.wei < dist[c.to]) // Optimización
				dp.push(Conn {c.to, c.wei + t.wei});
		}
	}

	return dist;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<Conn>> graph(n);
	vector<vector<Conn>> hparg(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--;
		b--;
		graph[a].push_back(Conn {b, c});
		hparg[b].push_back(Conn {a, c});
	}

	vector<ll> sdist = djk(graph, 0);
	vector<ll> edist = djk(hparg, n-1);

	vector<vector<int>> shor(n);
	// vector<vector<Conn>> rohs(n);
	for(int i = 0; i < n; ++i) for(Conn c : graph[i]) {
		if(sdist[i] + c.wei == sdist[c.to] &&
				edist[i] == edist[c.to] + c.wei) {
			shor[i].push_back(c.to);
		}
	}

	struct Info {
		ll mx_flights;
		ll mn_flights;
		ll num_routes;
	};

	vector<Info> dp(n, Info {-INF, INF, 0});
	dp[n-1].mx_flights = 0;
	dp[n-1].mn_flights = 0;
	dp[n-1].num_routes = 1;
	vector<bool> seen(n, false);
	seen[n-1] = true;
	function<void(int)> dfs = [&](int node) {
		if(seen[node]) return;
		seen[node] = true;
		for(int ch : shor[node]) {
			dfs(ch);
			dp[node].mx_flights = max(dp[node].mx_flights, dp[ch].mx_flights + 1);
			dp[node].mn_flights = min(dp[node].mn_flights, dp[ch].mn_flights + 1);
			dp[node].num_routes += dp[ch].num_routes;
			dp[node].num_routes %= mod;
		}
	};
	dfs(0);
	cout << edist[0] << " "
		<< dp[0].num_routes << " "
		<< dp[0].mn_flights << " "
		<< dp[0].mx_flights << endl;

}
