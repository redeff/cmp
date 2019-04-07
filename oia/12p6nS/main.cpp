#include <bits/stdc++.h>
using namespace std;

struct State {
	vector<int> crossed;
	int node;
	int dist;
	bool operator<(const State b) const {
		return dist == b.dist ? crossed.size() < b.crossed.size() : dist < b.dist;
	}
};

struct Conn {
	bool obs;
	int wei;
	int to;
	int index;
};

int main() {
#define cin lkdfhaskjdfh
#define cout sjdhfakjdhf
	ifstream cin("ciudad.in");
	ofstream cout("ciudad.out");
	int n, m, m1;
	cin >> n >> m >> m1;

	vector<vector<Conn>> graph(n);
	for(int i = 0; i < m + m1; ++i) {
		int a, b, wei;
		cin >> a >> b >> wei;
		a--; b--;

		graph[a].push_back(Conn {i >= m, wei, b, i});
		graph[b].push_back(Conn {i >= m, wei, a, i});
	}

	const int INF = 1000000000;
	vector<vector<State>> dist(n, vector<State>(3, State {{}, 0, INF}));
	priority_queue<State> dp;
	dp.push(State {{}, 0, 0});
	while(!dp.empty()) {
		State s = dp.top();
		dp.pop();
		if(dist[s.node][s.crossed.size()].dist != INF) continue;
		dist[s.node][s.crossed.size()] = s;
		dist[s.node][s.crossed.size()].dist *= -1;

		for(Conn c : graph[s.node]) {
			vector<int> edg = s.crossed;
			if(c.obs) edg.push_back(c.index);
			if(edg.size() <= 2) {
				dp.push(State {edg, c.to, s.dist - c.wei});
			}
		}
	}

	State s = *min_element(dist[n-1].begin(), dist[n-1].end());
	cout << s.crossed.size() + 1 << " ";
	for(int i : s.crossed) cout << i - m + 1 << " ";
	cout << s.dist << endl;
};
