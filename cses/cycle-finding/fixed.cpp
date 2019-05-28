#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Conn {
	int to;
	ll wei;
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<Conn>> graph(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		// graph[a-1].push_back(Conn {b-1, c});
		graph[b-1].push_back(Conn {a-1, c});
	}

	vector<ll> dist(n, 0);
	vector<int> from(n, -1);
	int delta = -1;
	for(int t = 0; t <= n; ++t) {
		for(int i = 0; i < n; ++i) {
			for(Conn c : graph[i]) {
				if(dist[c.to] > dist[i] + c.wei) {
					dist[c.to] = dist[i] + c.wei;
					from[c.to] = i;
					if(t == n) delta = c.to;
				}
			}
		}
	}

	// for(int i : from) cout << i << " ";
	// cout << endl;

	if(delta == -1) {
		cout << "NO" << endl;
	} else {
		int a = delta;
		int b = from[delta];
		while(a != b) {
			// cerr << a << " -> " << from[a] << endl;
			a = from[a];
			b = from[from[b]];
		}

		cout << "YES" << endl;
		cout << a+1;
		for(int i = from[a]; i != a; i = from[i]) {
			cout << " " << i+1;
		}
		cout << " " << a+1;
		cout << endl;
	}
}
