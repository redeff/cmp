#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int dist(pair<int, int> a, pair<int, int> b) {
	ll x = a.first - b.first;
	ll y = a.second - b.second;
	return 2 + int(sqrt(x * x + y * y));
}

int main() {
#ifndef LOLOLOL
	ifstream cin("parque.in");
	ofstream cout("parque.out");
#endif
	int n;
	cin >> n;
	vector<pair<int, int>> ns(n+1);
	ns[0] = {0, 0};
	for(int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		cin >> ns[k].first >> ns[k].second;
	}
	++n;

	vector<vector<int>> graph(n);

	priority_queue<pair<int, pair<int, int>>> pq;
	vector<bool> seen(n, false);
	pq.push({0, {0, 0}});
	int conn = 0;
	int total = 0;
	while(!pq.empty() && conn < n) {
		auto p = pq.top();
		pq.pop();
		int node = p.second.first;
		int pr = p.second.second;
		if(seen[node]) continue;
		seen[node] = true;
		conn++;
		total -= p.first;
		graph[pr].push_back(node);
		graph[node].push_back(pr);

		for(int i = 0; i < n; ++i) if(!seen[i]) {
			pq.push({-dist(ns[i], ns[node]), {i, node}});
		}
	}
	cout << total << endl;
	for(int i = 1; i < n; ++i) {
		cout << i;
		for(int j : graph[i]) cout << " " << j;
		cout << endl;
	}
}
