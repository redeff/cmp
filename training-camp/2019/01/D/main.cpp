#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

void caso() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	// g = vector<vector<int>>(n);
	forn(i, m) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	struct Frame {
		int node;
		int index;
	};

	// vector<int> color(n, 0);
	vector<Frame> st;
	vector<int> ord;
	vector<bool> seen(n, false);
	auto fun = [&](int node) {
		if(!seen[node]) {
			st.emplace_back(node, 0);
			ord.push_back(st.back().node);
			while(!st.empty()) {
				int f = st.back();
				if(f.index < graph[f.node].size()) {
					st.back().index++;
					int new_node = graph[f.node][f.index];
					if(!seen[new_node]) {
						st.emplace_back(graph[f.node][f.index], 0);
						ord.push_back(st.back().node);
					}
				} else {
					st.pop_back();
				}
			}
		}
	};

	forn(i, n) fun(i);

	{
		vector<vector<int>> ngraph;
		vector<int> inv(n);
		forn(i, n) inv[ord[i]] = i;
		forn(i, n) {
			ngraph[i] = graph[ord[i]];
			for(int & j : ngraph[i]) {
				j = inv[j];
			}
		}

		swap(graph, ngraph);
	}

	vector<int> color(n, 0);
	vector<int> depth(n, 0);
	forn(node, n) {
		if(color[node] == 0) color[node] = 1;
		for(int ch : graph[node]) if(ch > node) {
			color[ch] = -color[node];
			depth[ch] = 1 + depth[node];
		}
	}
}

int main() {
	int test;
	cin >> test;
	while(test --> 0) caso();
}
