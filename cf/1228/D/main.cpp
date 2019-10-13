#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<unordered_set<int>> graph(n);
	forn(sladkf, m) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].insert(b);
		graph[b].insert(a);
	}

	unordered_set<int> seen;
	forn(i, n) {
		seen.insert(i);
	}

	int cmp = 0;
	vector<int> cmps(n, -1);
	vector<int> sizes;
	while(!seen.empty()) {
		int k = *seen.begin();
		// seen.erase(k);

		vector<int> thcmp;
		for(int t : seen) {
			if(graph[k].count(t)) continue;
			thcmp.push_back(t);
		}

		sizes.push_back(0);
		for(int t : thcmp) {
			sizes.back()++;
			seen.erase(t);
			cmps[t] = cmp;
		}

		++cmp;
	}

	if(cmp != 3) {
		cout << -1 << endl;
	} else {
		forn(i, n) for(int j : graph[i]) {
			if(cmps[i] == cmps[j]) {
				cout << -1 << endl;
				return 0;
			}
		}

		if(m !=
				sizes[0] * sizes[1] +
				sizes[1] * sizes[2] +
				sizes[2] * sizes[0]) {
			cout << -1 << endl;
			return 0;
		}

		forn(i, n) cout << cmps[i]+1 << " ";
		cout << endl;
	}
}
