#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

// sum [0, node)
ll get_ft(vector<ll> &ft, int node) {
	ll total = 0;
	for(int x = node; x; x -= x & -x) {
		total += ft[x-1];
	}
	return total;
}

// A[node] += delta
void set_ft(vector<ll> &ft, int node, ll delta) {
	for(int x = node+1; x <= ft.size(); x += x & -x) {
		ft[x-1] += delta;
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, q;
	cin >> n >> q;

	vector<ll> vals(n);
	for(int i = 0; i < n; ++i) {
		cin >> vals[i];
	}

	vector<vector<int>> graph(n);
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> ord;
	vector<int> s(n);
	vector<int> e(n);
	function<void(int, int)> dfs = [&](int node, int dad) {
		s[node] = ord.size();
		ord.push_back(node);
		for(int ch : graph[node]) if(ch != dad) dfs(ch, node);
		e[node] = ord.size();
	};

	dfs(0, 0);

	vector<ll> ft(n, 0);
	for(int i = 0; i < n; ++i) set_ft(ft, s[i], vals[i]);

	for(int j = 0; j < q; ++j) {
		int t, i;
		cin >> t >> i;
		--i;

		if(t == 2) {
			cout << get_ft(ft, e[i]) - get_ft(ft, s[i]) << "\n";
		} else {
			ll x;
			cin >> x;
			set_ft(ft, s[i], x-vals[i]);
			vals[i] = x;
		}
	}
}
