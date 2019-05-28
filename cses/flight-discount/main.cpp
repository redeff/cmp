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

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<vector<Conn>> graph(2*n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		--a;
		--b;
		graph[a].push_back(Conn {b, c});
		graph[a+n].push_back(Conn {b+n, c});
		graph[a].push_back(Conn {b+n, c/2});
	}

	const ll INF = 33333333333333333;
	vector<ll> dist(2*n, INF);
	priority_queue<Conn> dik;
	dik.push(Conn {0, 0});
	while(!dik.empty()) {
		Conn t = dik.top();
		dik.pop();
		if(t.wei >= dist[t.to]) continue;
		dist[t.to] = t.wei;
		for(Conn c : graph[t.to]) {
			if(dist[c.to] > t.wei + c.wei) {
				dist[c.to] = t.wei + c.wei + 1;
				dik.push(Conn {c.to, t.wei + c.wei});
			}
		}
	}

	cout << dist.back() << "\n";
}
