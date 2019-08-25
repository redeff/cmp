#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

vector<int> leaves(vector<vector<int>> &graph, vector<vector<int>> &hparg) {
	int n = int(graph.size());

	vector<int> ns;
	vector<bool> seen(n, false);
	function<void(int)> dfs1 = [&](int node) {
		if(seen[node]) return;
		seen[node] = true;
		for(int ch: graph[node]) dfs1(ch);
		ns.push_back(node);
	};

	forn(i, n) dfs1(i);
	reverse(ns.begin(), ns.end());

	seen = vector<bool>(n, false);
	vector<int> color = vector<int>(n, -1);
	function<bool(int, int)> dfs2 = [&](int node, int col) {
		bool ret = false;
		if(color[node] != -1 && color[node] != col) ret = true;

		if(seen[node]) return ret;
		seen[node] = true;

		color[node] = col;
		for(int ch : hparg[node]) {
			if(dfs2(ch, col)) ret = true;
		}

		return ret;
	};

	vector<int> res;
	for(int i : ns) {
		if(!seen[i] && !dfs2(i, i)) {
			res.push_back(i);
		}
	}

	return res;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n);
	vector<vector<int>> hparg(n);

	forn(i, m) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		hparg[b].push_back(a);
	}

	auto as = leaves(graph, hparg);
	auto bs = leaves(hparg, graph);

	/*
	for(int i : as) cout << i << " ";
	cout << endl;
	for(int i : bs) cout << i << " ";
	cout << endl;
	*/


	/*
	bool swapped = false;
	if(bs.size() < as.size()) {
		swap(as, bs);
		swap(graph, hparg);
		swapped = true;
	}
	*/

	vector<int> color(n, -1);

	function<void(int, int)> dfs1 = [&](int node, int col) {
		if(color[node] != -1) return;
		color[node] = col;

		for(int ch : graph[node]) dfs1(ch, col);
	};

	for(int i : as) dfs1(i, i);
	swap(graph, hparg);
	auto dad = color;

	color = vector<int>(n, -1);
	for(int i : bs) dfs1(i, i);
	swap(graph, hparg);
	auto chi = color;

	vector<pair<int, int>> edges;
	for(int i : as) edges.push_back({i, chi[i]});
	for(int i : bs) if(i != dad[i]) edges.push_back({dad[i], i});

	vector<int> deg(n, 0);
	for(auto i : edges) {
		deg[i.first]++;
		if(i.first != i.second) deg[i.second]++;
		// deg[i.second]++;
	}

	// cerr << "---------" << endl;
	vector<vector<int>> red(n);
	for(auto i : edges) {
		// cerr << i.first << " " << i.second << endl;
		if(deg[i.first] == 1 || deg[i.second] == 1) {
			red[i.first].push_back(i.second);
			if(i.first != i.second) red[i.second].push_back(i.first);
			// cout << i.second+1 << " " << i.first+1 << endl;
		} else {
			deg[i.first]--;
			deg[i.second]--;
		}
	}

	forn(i, n) if(!red[i].empty()) {
		if(red[red[i][0]].size() == 1) { // deg of first child
			for(int ch : red[i]) if(ch != i) red[ch] = {};
		}
	}

	// cerr << "---------" << endl;
	vector<vector<int>> a_bunch;
	for(int i : as) {
		if(!red[i].empty()) {
			a_bunch.push_back(red[i]);
			a_bunch.back().push_back(i);
			// for(auto j : a_bunch.back()) cerr << j+1 << " ";
			// cerr << endl;
		}
	}
	// cerr << "--------" << endl;
	vector<vector<int>> b_bunch;
	for(int i : bs) {
		if(!red[i].empty() && dad[i] != i) {
			b_bunch.push_back(red[i]);
			b_bunch.back().push_back(i);
			// for(auto j : b_bunch.back()) cerr << j+1 << " ";
			// cerr << endl;
		}
	}

	vector<pair<int, int>> total;
	while(!a_bunch.empty() && !b_bunch.empty()) {
		total.push_back({a_bunch.back().back(), b_bunch.back().back()});
		a_bunch.back().pop_back();
		b_bunch.back().pop_back();
		// cerr << "LOOP" << endl;

		if(a_bunch.back().size() == 1) {
			// int t = b_bunch.back().back();
			// b_bunch.back().back() = a_bunch.back().back();
			b_bunch.back().push_back(a_bunch.back().back());
			a_bunch.pop_back();
			// cerr << "AAH" << endl;
			// b_bunch.back().push_back(t);
		}
		else if(b_bunch.back().size() == 1) {
			a_bunch.back().push_back(b_bunch.back().back());
			b_bunch.pop_back();
			/*
			int t = a_bunch.back().back();
			a_bunch.back().back() = b_bunch.back().back();
			b_bunch.pop_back();
			a_bunch.back().push_back(t);
			*/
		}
		else {
			swap(a_bunch.back().back(), b_bunch.back().back());
		}
	}

	forn(j, a_bunch.size()) {
		forn(index, a_bunch[j].size()-1) {
			int i = a_bunch[j][index];
			total.push_back({a_bunch[(j + 1) % a_bunch.size()].back(), i});
			if(total.back().first == total.back().second) total.pop_back();
		}
	}
	forn(j, b_bunch.size()) {
		forn(index, b_bunch[j].size()-1) {
			int i = b_bunch[j][index];
			total.push_back({i, b_bunch[(j + 1) % b_bunch.size()].back()});
			if(total.back().first == total.back().second) total.pop_back();
		}
	}

	cout << total.size() << endl;
	for(auto p : total) cout << p.second+1 << " " << p.first+1 << endl;

	/*
	forn(i, bs.size()) {
		int u = bs[i];
		int v = color[bs[(i+1)%bs.size()]];
		if(!as_set.count(v)) {
			if(as_set.empty()) {
				v = as[0];
			} else {
				v = *as_set.begin();
			}
		}
		as_set.erase(v);
		if(swapped) swap(u, v);
		cout << u+1 << " " << v+1 << endl;
	}
	*/
}
