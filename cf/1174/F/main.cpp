#include <bits/stdc++.h>
#define fore(i, z, n) for(int i = int(z); i < int(n); ++i)
using namespace std;

vector<vector<int>> graph;
vector<bool> centroid;
vector<int> depths;
vector<int> dads;

int n;
int total;

int nxt(int node) {
	cout << "s " << node+1 << endl;
	int res;
	cin >> res;
	return res-1;
}

int dist(int node) {
	cout << "d " << node+1 << endl;
	int res;
	cin >> res;
	if(res == 0) {
		cout << "! " << node+1 << endl;
		exit(0);
	}
	return res;
}

int pa_donde(int root) {
	int k = dist(root);
	if(total == k + depths[root]) {
		return nxt(root);
	} else {
		return dads[root];
	}
}

void rec(int root) {
	vector<int> sizes(n, 0);
	function<void(int, int)> dfs = [&](int node, int dad) {
		if(centroid[node]) return;
		sizes[node] = 1;
		for(int ch : graph[node]) if(dad != ch) {
			dfs(ch, node);
			sizes[node] += sizes[ch];
		}
	};
	dfs(root, root);

	function<int(int, int)> find_good = [&](int node, int dad) {
		if(2*sizes[node] < sizes[root]) return -1;
		for(int ch : graph[node]) if(dad != ch) {
			int r = find_good(ch, node);
			if(r != -1) return r;
		}
		return node;
	};
	int cent = find_good(root, root);
	centroid[cent] = true;
	rec(pa_donde(cent));
}

int main() {
	cin >> n;
	graph = vector<vector<int>>(n);
	centroid = vector<bool>(n, false);
	dads = vector<int>(n, -1);
	depths = vector<int>(n, -1);
	fore(i, 0, n-1) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	total = dist(0);

	function<void(int)> dfs = [&](int node) {
		for(int ch : graph[node]) if(ch != dads[node]) {
			dads[ch] = node;
			depths[ch] = depths[node] + 1;
			dfs(ch);
			// sizes[node] += sizes[ch];
		}
	};
	dads[0] = 0;
	depths[0] = 0;
	dfs(0);

	rec(0);
}
