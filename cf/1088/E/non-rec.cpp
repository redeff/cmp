#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 333333333;

struct Node {
	ll parent;
	vector<ll> children;
};

vector<int> order(vector<vector<int>> &tree, int root) {
	struct State {
		int child;
		int node;
		int dad;
	};

	vector<State> s;
	vector<int> out;

	s.push_back({0, 0, 0});

	while(!s.empty()) {
		State last = s.back();
		if(last.child == (ll)tree[last.node].size()) {
			s.pop_back();
			out.push_back(last.node);
		} else {
			s.back().child++;
			if(tree[last.node][last.child] != last.dad) {
				s.push_back({0, tree[last.node][last.child], last.node});
			}
		}
	}

	return out;
}

int main() {
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<ll> weis(n);
	for(int i = 0; i < n; ++i) cin >> weis[i];

	vector<vector<int>> conns(n);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		conns[a].push_back(b);
		conns[b].push_back(a);
	}

	vector<int> indices = order(conns, 0);

	vector<ll> global_max(n, 0);
	for(int node : indices) {
		global_max[node] = weis[node];
		for(int ch : conns[node]) global_max[node] += max(global_max[ch], 0ll);

	}

	ll mx = *max_element(global_max.begin(), global_max.end());
	int total = 0;

	global_max.resize(0);
	global_max.shrink_to_fit();

	vector<ll> fit_all(n, 0);
	for(int node : indices) {
		fit_all[node] = weis[node];
		for(int ch : conns[node]) {
			fit_all[node] += max(fit_all[ch], 0ll);
		}
		if(fit_all[node] == mx) {
			fit_all[node] = 0;
			total++;
		}
	}

	cout << mx * (ll)total << " " << total << endl;
}
