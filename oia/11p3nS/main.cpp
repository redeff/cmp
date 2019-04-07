#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
#ifndef TEST
#define cin cina
#define cout couta
	ifstream cin("congestion.in");
	ofstream cout("congestion.out");
#endif
	int n, m;
	cin >> n >> m;

	vector<ll> cross(m, 0);
	vector<int> to(m);
	vector<ll> wei(m);

	vector<vector<int>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a;
		cin >> a >> to[i] >> wei[i];
		a--; to[i]--;

		graph[a].push_back(i);
	}

	const ll INF = 10000000000ll;

	for(int start = 0; start < n; ++start) {
		vector<ll> dist(n, INF);
		vector<bool> seen(n, false);
		vector<int> from(n, -1);
		priority_queue<pair<int, int>> pq;
		pq.push({-0, start});
		dist[start] = 0;

		while(!pq.empty()) {
			auto p = pq.top();
			pq.pop();
			if(!seen[p.second]) {
				seen[p.second] = true;
				// dist[p.second] = -p.first;
				for(int con : graph[p.second]) if(dist[to[con]] > wei[con] - p.first) {
					pq.push({p.first - wei[con], to[con]});
					dist[to[con]] = wei[con] - p.first;
				}
			}
		}

		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) {
			return dist[a] > dist[b];
		});
		
		vector<int> dp(n, 1);
		for(int i = 0; i < n; ++i) {
			for(int con : graph[ord[i]]) if(dist[to[con]] == wei[con] + dist[ord[i]]) {
				dp[ord[i]] += dp[to[con]];
				cross[con] += dp[to[con]];
			}
		}
	}

	vector<int> conns(m);
	iota(conns.begin(), conns.end(), 0);
	sort(conns.begin(), conns.end(), [&](int a, int b) {
		return cross[a] > cross[b];
	});

	while(cross[conns.front()] > cross[conns.back()]) conns.pop_back();
	cout << conns.size() << " " << cross[conns.back()] << endl;
	for(int i : conns) cout << i + 1 << endl;
}
