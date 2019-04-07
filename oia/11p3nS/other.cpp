#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Conn {
	int index;
	ll wei;
	int to;
	int from;
	ll cross;
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<Conn>> graph(n);
	for(int i = 0; i < m; ++i) {
		ll a, b, wei;
		cin >> a >> b >> wei;
		a--; b--;
		Conn c = Conn {.index=i, .wei=wei, .to=b, .from=a, .cross=0};
		graph[a].push_back(c);
		// graph[b].push_back(Conn {.index=i, .wei=wei, .to=a});
	}

	const ll INF = 10000000000ll;

	vector<vector<ll>> dist(n, vector<ll>(n, INF));
	// for(int i = 0; i < n; ++i) dist[i][i] = 0;

	for(int start = 0; start < n; ++start) {
		priority_queue<pair<ll, int>> pq;
		pq.push({0, start});

		while(!pq.empty()) {
			auto p = pq.top();
			pq.pop();
			if(-p.first >= dist[start][p.second]) continue;
			else {
				dist[start][p.second] = -p.first;
				for(Conn con : graph[p.second]) {
					pq.push({p.first - con.wei, con.to});
				}
			}
		}

		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) {
			return dist[start][a] > dist[start][b];
		});

		vector<int> dp(n, 1);
		for(int i = 0; i < n; ++i) {
			for(Conn &c : graph[ord[i]]) {
				if(dist[ord[i]] < dist[c.to]) {
					dp[ord[i]] += dp[c.to];
					c.cross += dp[c.to];
				}
			}
		}
	}

	vector<Conn> conns(m);
	for(auto &v : graph) for(Conn c : v) conns[c.index] = c;
	sort(conns.begin(), conns.end(), [&](Conn a, Conn b) {return a.cross > b.cross;});
	while(conns.front().cross > conns.back().cross) conns.pop_back();
	cout << conns.size() << " " << conns.back().cross << endl;
	for(Conn c : conns) cout << c.index + 1 << " ";
	cout << endl;
}
