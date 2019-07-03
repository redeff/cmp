#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> deg(n, 0);
	vector<vector<int>> graph(n);

	forn(i, m) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[b].push_back(a);
		deg[a]++;
	}

	set<int> topo;
	forn(i, n) if(deg[i] == 0) topo.insert(i);
	vector<int> res;
	while(!topo.empty()) {
		int a = *topo.rbegin();
		topo.erase(a);
		res.push_back(a);

		for(int ch : graph[a]) {
			deg[ch]--;
			if(deg[ch] == 0) topo.insert(ch);
		}
	}

	reverse(res.begin(), res.end());
	for(int i : res) cout << i+1 << " ";
	cout << endl;
}
