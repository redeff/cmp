#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ll;

struct Conn {
	int to;
	int tag;
};

ll invert(ll a) {
	ll res = a;
	for(int i = 0; i < 6; ++i) {
		res = res * (2 - res * a);
	}

	assert(res * a == 1);
	return res;
}

ll base;
ll inv;

ll get_ash(string s) {
	ll ash = 0;
	for(char c : s) {
		ash *= base;
		ash += c - 'a' + 1;
	}

	return ash;
}

int occur(vector<char> s, int len, ll ash) {
	if(s.size() < len) return 0;
	ll po = 1;
	ll roll = 0;
	for(int i = 0; i < len; ++i) {
		roll *= base;
		roll += s[i];
		po *= base;
	}

	int total = 0;
	if(roll == ash) total++;
	for(int i = len; i < s.size(); ++i) {
		roll *= base;
		roll += s[i] - 'a' + 1;
		roll -= s[i-len] * po;
		if(roll == ash) total++;
	}

	return total;
}

const int LCA = 17;

pair<vector<vector<int>>, vector<int>> lca_dads(vector<vector<Conn>> &tree) {
	int n = int(tree.size());
	vector<vector<int>> dads(n);
	vector<int> depths(n);
	function<void(int, int, int)> dfs = [&](int node, int dad, int depth) {
		assert(dads[node].empty());
		dads[node].push_back(dad);
		depths[node] = depth;
		for(Conn ch : tree[node]) if(ch.to != dad) {
			dfs(ch.to, node, depth+1);
		}
	};

	dfs(0, 0, 0);

	for(int l = 0; l < LCA; ++l) {
		for(int i = 0; i < n; ++i) {
			dads[i].push_back(dads[dads[i][l]][l]);
		}
	}

	for(int i = 0; i < n; ++i) assert(dads[i].size() == LCA+1);

	return {dads, depths};
}

struct Query {
	int node;
	ll ash;
};


pair<vector<Conn>, vector<int>> batch_queries(vector<vector<Conn>> &tree,
		vector<Query> qs) {

	int n = int(tree.size());
	vector<Conn> dads(n);
	function<void(int, int)> dfs1 = [&](int node, int dad) {
		for(Conn ch : tree[node]) if(ch.to != dad) {
			dads[ch.to] = Conn {to: node, tag: ch.tag};
			dfs1(ch.to, node);
		}
	};
	dfs1(0, -1);

	vector<vector<pair<int, int>>> ata(n);

	unordered_map<ll, int> useful;

	int cnt = 0;
	int index = 0;
	for(Query q : qs) {
		if(!useful.count(q.ash)) useful[q.ash] = ++cnt;
		ata[q.node].push_back({useful[q.ash], index});
		++index;
	}

	vector<int> dp(cnt+1, 0);
	vector<int> res(qs.size());

	function<void(int, int)> dfs = [&](int node, int dad) {
		ll ash = 0;
		for(int i = node; i != 0; i = dads[i].to) {
			ash *= base;
			ash += dads[i].tag;
			// if(useful.count(ash)) dp[useful[ash]]++;
			dp[useful[ash]]++;
		}
		for(auto p : ata[node]) {
			res[p.second] = dp[p.first];
		}
		for(Conn ch : tree[node]) if(ch.to != dad) {
			dfs(ch.to, node);
		}
		ash = 0;
		for(int i = node; i != 0; i = dads[i].to) {
			ash *= base;
			ash += dads[i].tag;
			dp[useful[ash]]--;
			// if(useful.count(ash)) dp[useful[ash]]--;
		}
	};

	dfs(0, 0);

	return {dads, res};
}

int main() {
	int n;
	cin >> n;

	vector<vector<Conn>> ns(n);
	ll seed = 190238;
	for(int i = 0; i < n-1; ++i) {
		int a, b;
		string c;
		cin >> a >> b >> c;
		--a; --b;
		ns[a].push_back(Conn {b, c[0] - 'a' + 1});
		ns[b].push_back(Conn {a, c[0] - 'a' + 1});
		seed ^= a;
		seed <<= 5;
		seed ^= b;
		seed *= c[0] - 'a' + 1;
	}
	{
		srand((unsigned)seed);
		rand();
		rand();
		rand();
		base = ll(rand()) * ll(rand()) * 2 + 1;
		inv = invert(base);
	}

	struct Big_Query {
		int a;
		int b;
		ll ash;
		ll rash;
		int index;
		int len;
		int l;
	};
	vector<Query> batch;
	auto lala = lca_dads(ns);
	auto dads = lala.first;
	auto depths = lala.second;

	auto at_depth = [&](int a, int d) {
		/*
		d = depths[a] - d;
		if(d < 0) return a;
		for(int i = 0; i < LCA; ++i) if(i & d) {
			a = dads[a][i];
		}
		*/
		for(int l = LCA; l >= 0; --l) {
			if(depths[dads[a][l]] >= d) {
				a = dads[a][l];
			}
		}
		return a;
	};

	auto lca = [&](int a, int b) {
		if(depths[a] > depths[b]) swap(a, b);
		for(int l = LCA; l >= 0; --l) {
			if(depths[dads[b][l]] >= depths[a]) b = dads[b][l];
		}
		if(a == b) return a;
		assert(depths[a] == depths[b]);
		for(int l = LCA; l >= 0; --l) {
			if(dads[a][l] != dads[b][l]) {
				a = dads[a][l];
				b = dads[b][l];
			}
		}
		assert(dads[a][0] == dads[b][0]);
		return dads[a][0];
	};

	int q;
	cin >> q;
	vector<Big_Query> qs(q);
	for(auto &p : qs) {
		int a, b;
		string s;
		cin >> a >> b >> s;
		--a;
		--b;
		p.a = a;
		p.b = b;
		p.ash = get_ash(s);
		reverse(s.begin(), s.end());
		p.rash = get_ash(s);
		p.index = int(batch.size());
		p.len = int(s.size());

		int l = lca(a, b);
		p.l = l;
		batch.push_back(Query {node : p.a, ash : p.ash});
		batch.push_back(Query {node : l, ash : p.ash});
		batch.push_back(Query {node : p.b, ash : p.rash});
		batch.push_back(Query {node : l, ash : p.rash});
		// batch.push_back(Query {node : v, ash : ash});
	}

	auto caca = batch_queries(ns, batch);
	// vector<int> res = batch_queries(ns, batch);
	vector<int> res = caca.second;
	vector<Conn> label = caca.first;

	for(auto p : qs) {
		int total = res[p.index] - res[p.index + 1] + res[p.index + 2] - res[p.index + 3];
		int a = at_depth(p.a, depths[p.l] + p.len - 1);
		assert(at_depth(p.a, depths[p.l]) == p.l);
		int b = at_depth(p.b, depths[p.l] + p.len - 1);
		assert(at_depth(p.b, depths[p.l]) == p.l);
		vector<char> s;
		while(a != p.l) {
			// cerr << a << endl;
			// return 0;
			s.push_back(label[a].tag);
			a = label[a].to;
		}
		vector<char> sb;
		while(b != p.l) {
			sb.push_back(label[b].tag);
			b = label[b].to;
		}
		reverse(sb.begin(), sb.end());
		for(int c : sb) s.push_back(c);
		total += occur(s, p.len, p.ash);
		cout << total << endl;
	}
}
