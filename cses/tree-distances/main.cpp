#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<int>> graph(n);
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> dads(n);
	vector<int> mx(n, 0);
	vector<int> snd(n, 0);
	vector<int> bd(n, 0);
	vector<int> ord;
	function<void(int)> dfs = [&](int node) {
		ord.push_back(node);

		vector<int> part(graph[node].size(), 0);
		for(int ch : graph[node]) {
			if(ch != dads[node]) {
				dads[ch] = node;
				dfs(ch);
				// if(mx[node] > snd[
				snd[node] = max(snd[node], mx[ch] + 1);
				if(snd[node] > mx[node]) {
					bd[node] = ch;
					swap(snd[node], mx[node]);
				}
			}
		}
	};


	dads[0] = -1;
	dfs(0);

	vector<int> up(n, 0);
	for(int node : ord) {
		for(int ch : graph[node]) if(ch != dads[node]) {
			if(ch == bd[node]) up[ch] = max(up[ch], snd[node]+1);
			else up[ch] = max(up[ch], mx[node]+1);

			up[ch] = max(up[ch], up[node]+1);
		}
	}

	for(int i = 0; i < n; ++i) cout << max(mx[i], up[i]) << " ";
	cout << endl;

	/*
	vector<int> mx(n, 0);
	for(int node : ord) {
		mx[dads[node]] = max(mx[dads[node]], mx[node] + 1);
	}
	*/

	/*
	vector<int> pre(n, 0);
	reverse(ord.begin(), ord.end());
	for(int node : ord) {
		vector<int> r(graph[node].size()+1, 0);
		vector<int> l(graph[node].size(), 0);
		for(int i = 0; i < graph[node].size(); ++i) {
			r[i+1] = r[i];
			if(dads[node] != graph[node][i]) {
				r[i+1] = max(r[i+1], 1 + mx[graph[node][i]]);
			}
		}
	}
	*/

}
