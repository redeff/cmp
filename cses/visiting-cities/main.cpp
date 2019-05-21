#include <bits/stdc++.h>
using namespace std;

typedef long long unsigned int ull;
typedef long long int ll;
ull ulrand() {
	return ull(rand()) + (ull(rand()) << 32ull);
}

struct Conn {
	int to;
	ll price;
};

bool operator<(Conn a, Conn b) {
	return a.price > b.price;
}

const ll INF = 33333333333333333ll;
vector<ll> djk(vector<vector<Conn>> &graph, int start) {
	int n = graph.size();
	vector<ll> dist(n, INF);

	priority_queue<Conn> dp;
	dp.push(Conn {start, 0});

	while(!dp.empty()) {
		Conn t = dp.top();
		dp.pop();
		if(dist[t.to] <= t.price) continue;
		dist[t.to] = t.price;
		for(Conn ch : graph[t.to]) {
			dp.push(Conn {ch.to, t.price + ch.price});
		}
	}

	return dist;
}

int main() {
	srand(910183048ull);
	int n, m;
	cin >> n >> m;

	vector<vector<Conn>> graph(n);
	vector<vector<Conn>> hparg(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--; b--;
		graph[a].push_back(Conn {b, c});
		hparg[b].push_back(Conn {a, c});
	}

	vector<ll> sdist = djk(graph, 0);
	vector<ll> edist = djk(hparg, n-1);

	vector<vector<int>> ngraph(n);
	vector<vector<int>> rgraph(n);
	for(int i = 0; i < n; ++i) {
		for(Conn c : graph[i]) {
			if(sdist[i] + c.price == sdist[c.to]
					&& edist[i] - c.price == edist[c.to]) {
				// cerr << i << " ~ " << c.to << endl;
				ngraph[i].push_back(c.to);
				rgraph[c.to].push_back(i);
			}
		}
	}

	vector<ull> val(n, 0);
	vector<bool> seen(n, false);
	val[0] = 1;
	// seen[s] = true;
	function<void(int)> dfs = [&](int node) {
		// cerr << "A" << endl;
		if(seen[node]) return;
		seen[node] = true;
		for(int p : rgraph[node]) dfs(p);
		if(ngraph[node].size() == 0) return;
		ull total = 0ull;
		for(int ch : ngraph[node]) {
			ull r = ulrand();
			val[ch] += r;
			total += r;
		}

		val[ngraph[node].front()] -= total;
		val[ngraph[node].front()] += val[node];
	};

	dfs(n-1);

	// for(int i = 0; i < n; ++i) cout << val[i] << " ";
	// cout << endl;

	int total = 0;
	for(int i = 0; i < n; ++i) if(val[i] == 1ull) {
		total++;
	}
	cout << total << endl;
	for(int i = 0; i < n; ++i) if(val[i] == 1ull) {
		cout << i + 1 << " ";
	}
	cout << endl;
}
