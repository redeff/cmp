#include <bits/stdc++.h>
using namespace std;

const int INF = 33333;

vector<int> merge(vector<int> &a, vector<int> &b) {
	a.push_back(INF);
	b.push_back(INF);

	vector<int> res;
	int ap = 0;
	int bp = 0;
	while(ap < a.size() && bp < b.size()) {
		if(a[ap] < b[bp]) {
			res.push_back(a[ap]);
			ap += 1;
		} else if (a[ap] > b[bp]) {
			res.push_back(b[bp]);
			bp += 1;
		} else {
			res.push_back(b[bp]);
			ap++;
			bp++;
		}
	}
	a.pop_back();
	b.pop_back();
	res.pop_back();
	return res;
}

int main() {
	int n, m;
	cin >> n >> m;
	// Adj matrix
	vector<vector<bool>> gs(n, vector<bool>(n, false));
	vector<unordered_set<int>> cs(n);

	vector<int> repr(n);
	vector<vector<int>> sets(n);
	for(int i = 0; i < n; ++i) {
		sets[i] = {i};
		repr[i] = i;
	}

	for(int i = 0; i < m; ++i) {	
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if(gs[a][b]) { // Disconnect
			gs[a][b] = false;
			gs[b][a] = false;
			cs[a].erase(b);
			cs[b].erase(a);
			int rb = repr[b];
			sets.push_back(sets[repr[a]]);
			vector<bool> seen(n, false);
			function<void(int)> explore;

			bool explored_b = false;

			explore = [&](int k) {
				if(k == b) explored_b = true;
				if(seen[k]) return;
				seen[k] = true;
				repr[k] = sets.size() - 1;
				for(int o : cs[k]) {
					explore(o);
				}
			};
			explore(a);
			if(explored_b) {
				vector<int>().swap(sets[rb]);
			}

		} else { // Connect
			gs[a][b] = true;
			gs[b][a] = true;
			cs[a].insert(b);
			cs[b].insert(a);
			if(repr[a] != repr[b]) {
				sets.push_back(merge(sets[repr[a]], sets[repr[b]]));
				int ra = repr[a];
				int rb = repr[b];
				for(int i = 0; i < n; ++i) {
					if(repr[i] == ra || repr[i] == rb)
						repr[i] = sets.size() - 1;
				}
				vector<int>().swap(sets[ra]);
				vector<int>().swap(sets[rb]);
			}
		}
	}

	for(int i = 0; i < n; ++i) cout << sets[repr[i]].size() << endl;
	/*
	for(int i = 0; i < sets.size(); ++i) {
		for(auto s : sets[i]) {
			cerr << s << " ";
		} cerr << endl;
	}
	*/
}
