#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, q;
	cin >> n >> q;
	vector<int> to(n);
	vector<vector<int>> rev(n);
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		--a;
		to[i] = a;
		rev[a].push_back(i);
	}

	vector<bool> loop(n, false);
	vector<int> component(n, -1);
	vector<int> joint(n, -1);
	vector<int> angle(n, -1);
	vector<int> size(n, -1);
	vector<int> depth(n, -1);
	vector<int> lo(n, -1);
	vector<int> hi(n, -1);

	int index = 0;

	for(int j = 0; j < n; ++j) if(component[j] == -1) {
		int a = j;
		int b = to[j];
		while(a != b) {
			a = to[a];
			b = to[to[b]];
		}

		int i = a;
		int ang = 0;
		do {
			loop[i] = true;
			angle[i] = ang;

			i = to[i];
			ang++;
		} while(i != a);

		do {
			size[i] = ang;
			// component[i] = a;
			function<void(int, int)> dfs = [&](int node, int dep) {
				lo[node] = index;
				depth[node] = dep;
				component[node] = a;
				joint[node] = i;
				for(int ch : rev[node]) if(!loop[ch]) {
					dfs(ch, dep + 1);
				}
				hi[node] = ++index;
			};

			dfs(i, 0);

			i = to[i];
		} while(i != a);
	}

	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		if(joint[a] == joint[b]) {
			if(lo[b] <= lo[a] && hi[a] <= hi[b]) {
				cout << depth[a] - depth[b];
			} else {
				cout << -1;
			}
		} else if(!loop[b] || component[a] != component[b]) {
			cout << -1;
		} else {
			int d = angle[b] - angle[joint[a]];
			if(d < 0) d += size[b];
			cout << depth[a] + d;
		}

		cout << endl;
	}
}
