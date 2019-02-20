#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 1000000007;

struct Tree {
	vector<int> ch;
	int dad;
	ll val;
};

void acc(int root, vector<Tree> &tree) {
	for(int ch: tree[root].ch) {
		acc(ch, tree);
		tree[root].val ^= tree[ch].val;
	}
}

void rev(int root, vector<Tree> &tree) {
	for(int ch: tree[root].ch) {
		tree[root].val ^= tree[ch].val;
		rev(ch, tree);
	}
}

ll filter(ll x, int root, vector<Tree> &tree, vector<int> &v) {
	ll total = 0;
	if(tree[root].val == 0 || tree[root].val == x) {
		total++;
		vector<int> own;
		for(int ch : tree[root].ch) {
			total += filter(x, ch, tree, own);
		}
		tree[root].ch = own;
		v.push_back(root);
	} else {
		for(int ch : tree[root].ch) {
			total += filter(x, ch, tree, v);
		}
	}
	return total;
}

struct Ways {
	ll o;
	ll e;
};

Ways operator+(Ways one, Ways two) {
	ll o = 0;
	o += one.o * two.o % MOD;
	o %= MOD;
	o += one.o * two.e % MOD;
	o %= MOD;
	o += one.e * two.o % MOD;
	o %= MOD;

	ll e = 0;
	e += one.e * two.o % MOD;
	e %= MOD;
	e += one.e * two.e % MOD;
	e %= MOD;
	e += one.o * two.o % MOD;
	e %= MOD;

	return Ways{o, e};
}

Ways calc(int root, vector<Tree> &tree) {
	Ways curr;
	if(tree[root].val == 0) curr = Ways{0, 1};
	else curr = Ways{1, 0};

	for(int ch: tree[root].ch) {
		Ways rec = calc(ch, tree);
		curr = curr + rec;
	}

	return curr;
}

int main() {
	int n;
	cin >> n;
	ll x;
	cin >> x;

	vector<ll> weis(n);
	for(int i = 0; i < n; ++i) cin >> weis[i];

	vector<vector<int>> graph(n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	vector<Tree> tree(n);

	function<void(int, int)> dfs = [&](int node, int dad) {
		tree[node].val = weis[node];
		for(int ch : graph[node]) if(ch != dad) {
			tree[node].ch.push_back(ch);
			dfs(ch, node);
		}
	};

	dfs(0, -1);

	acc(0, tree);
	vector<int> v;
	ll total = filter(x, 0, tree, v);

	if(v.size() != 1) {
		cout << "0" << endl;
		return 0;
	}

	if(x == 0) {
		ll res = 1;
		for(int i = 1; i < total; ++i) {
			res *= 2;
			res %= MOD;
		}

		cout << res << endl;
		return 0;
	}

	rev(0, tree);
	Ways w = calc(0, tree);
	cout << ((x == 0) ? w.e : w.o) << endl;
}
