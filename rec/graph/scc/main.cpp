#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

vector<vector<int>> transpose(vector<vector<int>> &graph) {
	int n = int(graph.size());
	vector<vector<int>> hparg(n);
	forn(i, n) {
		for(int ch : graph[i]) {
			hparg[ch].push_back(i);
		}
	}

	return hparg;
}

vector<int> finish_order(vector<vector<int>> &graph) {
	int n = int(graph.size());

	vector<int> color(n, 0);
	vector<int> finishing;

	auto dfs = [&](int root) {
		vector<int> st = {root};
		assert(color[root] == 0);
		while(!st.empty()) {
			int node = st.back();
			if(color[node] == 1) {
				st.pop_back();
				color[node] = 2;
				finishing.push_back(node);
				continue;
			}
			assert(color[node] == 0);
			color[node] = 1;

			for(int ch : graph[node]) if(color[node] == 0) {
				st.push_back(ch);
			}
		}
	};

	forn(i, n) if(color[i] == 0) dfs(i);

	return finishing;
}

vector<int> scc(vector<vector<int>> &graph) {
	int n = int(graph.size());
	vector<int> finishing = finish_order(graph);
	reverse(finishing.begin(), finishing.end());

	auto hparg = transpose(graph);

	vector<int> color(n, -1);
	auto dfs = [&](int root) {
		// assert(color[node] == -1);
		vector<int> st = {root};
		while(!st.empty()) {
			int node = st.back();
			st.pop_back();
			if(color[node] != -1) continue;
			color[node] = root;
			for(int ch : graph[node]) st.push_back(ch);
		}
	};

	for(int node : finishing) {
		cerr << "process" << endl;
		dfs(node);
	}

	return color;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	forn(i, m) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}

	auto color = scc(graph);
	forn(i, n) {
		cerr << i << " " << color[i] << endl;
	}
}
