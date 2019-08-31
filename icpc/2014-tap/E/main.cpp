#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;
int main() {
	int m, n;
	cin >> m >> n;

	vector<vector<int>> graph(n);
	forn(i, m) {
		int p = graph.size();
		graph.emplace_back();
		++n;

		int c;
		cin >> c;
		forn(lala, c) {
			int t;
			cin >> t;
			--t;
			graph[t].push_back(p);
			graph[p].push_back(t);
		}
	}

	vector<int> bfs = {0};
	vector<int> dist(n, -1);
	int d = 0;
	while(!bfs.empty()) {
		vector<int> nbfs;
		for(int node : bfs) {
			if(dist[node] != -1) continue;
			dist[node] = d;
			for(int ch : graph[node]) nbfs.push_back(ch);
		}
		swap(nbfs, bfs);
		++d;
	}
	int num = 0;
	int sum = 0;
	int mx = 0;
	for(int i : dist) if(i % 2 == 0) {
		i /= 2;
		mx = max(mx, i);
		sum += i;
		num++;
	}

	cout << num << " " << mx << " " << sum << endl;
}
