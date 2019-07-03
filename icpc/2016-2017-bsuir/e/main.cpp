#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector<vector<int>> tree(n);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	vector<vector<pair<int, int>>> queries(n);

	for(int i = 0; i < q; ++i) {
		int v, k;
		cin >> v >> k;

		--v;
		queries[v].push_back({i, k});
	}

	vector<int> sizes(n, 1);
	ordered_set curr;
	int tim = 0;
	function<void(int, int)> dfs1 = [&](int node, int dad) {
		for(int ch : tree[node]) if(ch != dad) {
			dfs1(ch, node);
			sizes[node] += sizes[ch];
		}

		tim++;
		curr.insert({sizes[node], tim});
	};

	dfs1(0, -1);

	vector<int> res(q);

	function<void(int, int)> dfs2 = [&](int node, int dad) {
		// for(auto i : curr) cerr << i << " ";
		// cerr << endl;
		for(auto p : queries[node]) {
			res[p.first] = curr.find_by_order(p.second-1)->first;
		}
		for(int ch : tree[node]) if(ch != dad) {
			curr.erase(curr.lower_bound({sizes[ch], 0}));
			tim++;
			curr.insert({n - sizes[ch], tim});
			dfs2(ch, node);
			curr.erase(curr.lower_bound({n - sizes[ch], 0}));
			tim++;
			curr.insert({sizes[ch], tim});
		}
	};
	dfs2(0, -1);

	for(int i : res) cout << i << "\n";
}
