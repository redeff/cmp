#include <bits/stdc++.h>
using namespace std;

void caso() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(2*n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b+n);
		graph[a+n].push_back(b);
		graph[b].push_back(a+n);
		graph[b+n].push_back(a);
	}

	struct Frame {
		int node;
		int index;
	};

	vector<int> color(2*n, 0);
	vector<int> comp(2*n, -1);

	vector<Frame> st;
	auto fun = [&](int node) {
		if(comp[node] == -1) {
			st.push_back(Frame {node:node, index:0});
			color[node] = 1;
			comp[node] = node;
			while(!st.empty()) {
				if(st.back().index == graph[st.back().node].size()) {
					color[st.back().index] = 2;
					st.pop_back();
				} else {
					int new_node = graph[st.back().node][st.back().index];
					st.back().index++;
					if(color[new_node] == 0) {
						int oth = (new_node + n) % (2*n);
						if(color[oth] != 1) {
							color[new_node] = 1;
							comp[new_node] = node;
							st.push_back(Frame {node:new_node, index:0});
						} else {
							comp[new_node] = node;
						}
					}
				}
			}
		}
	};

	for(int i = 0; i < 2*n; ++i) fun(i);
	int total = 0;
	for(int i = 0; i < n; ++i) cerr << comp[i] << " " << comp[i+n] << endl;
	cout << total << endl;
	cerr << "LALA" << endl;
}

int main() {
	int test;
	cin >> test;
	while(test --> 0) caso();
}
