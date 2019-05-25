#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;

	vector<vector<int>> graph(n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> dads(n);
	dads[0] = 0;

	vector<int> bag = {0};
	vector<int> ord;
	while(!bag.empty()) {
		int i = bag.back(); bag.pop_back();
		ord.push_back(i);
		for(int ch : graph[i]) if(ch != dads[i]) {
			dads[ch] = i;
			bag.push_back(ch);
		}
	}

	vector<ll> sub(n, 0);
	vector<ll> siz(n, 1);
	for(int i = n-1; i > 0; --i) {
		int node = ord[i];
		siz[dads[node]] += siz[node];
		sub[dads[node]] += sub[node] + siz[node];
	}

	vector<ll> tot(n, 0);
	tot[0] = sub[0];
	for(int i = 0; i < n; ++i) {
		int node = ord[i];
		if(node != 0) {
			tot[node] = tot[dads[node]] + n - 2ll * siz[node];
		}
	}

	for(ll i : tot) cout << i << " ";
	cout << "\n";
}
