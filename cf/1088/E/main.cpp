#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 333333333;

struct Node {
	ll parent;
	vector<ll> children;
};

int main() {
	ll n;
	cin >> n;
	vector<ll> weis(n);
	for(ll i = 0; i < n; ++i) cin >> weis[i];

	vector<vector<ll>> conns(n);
	for(ll i = 0; i < n - 1; ++i) {
		ll a, b;
		cin >> a >> b;
		--a; --b;
		conns[a].push_back(b);
		conns[b].push_back(a);
	}

	vector<ll> depths(n, INF);

	{
		function<void(ll, ll)> dfs = [&](ll node, ll depth) {
			if(depths[node] > depth) {
				depths[node] = depth;
				for(ll conn : conns[node]) dfs(conn, depth + 1);
			}
		};

		dfs(0, 0);
	}

	vector<Node> tree(n);
	for(int i = 0; i < n; ++i) {
		for(ll conn : conns[i]) {
			if(depths[conn] < depths[i]) tree[i].parent = conn;
			else tree[i].children.push_back(conn);
		}
	}

	tree[0].parent = 0;

	vector<ll> global_max(n);
	{
		function<void(ll)> dfs = [&](ll node) {
			global_max[node] = weis[node];
			for(ll ch : tree[node].children) {
				dfs(ch);
				global_max[node] += max(global_max[ch], 0ll);
			}
		};
		dfs(0);
	}

	ll mx = *max_element(global_max.begin(), global_max.end());
	ll total = 0;

	vector<ll> fit_all(n);
	{
		function<void(ll)> dfs = [&](ll node) {
			global_max[node] = weis[node];
			for(ll ch : tree[node].children) {
				dfs(ch);
				global_max[node] += max(global_max[ch], 0ll);
			}
			if(global_max[node] == mx) {
				global_max[node] = 0;
				total++;
			}
		};
		dfs(0);
	}

	cout << mx * total << " " << total << endl;
}
