#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef unsigned long long int ll;
// unsigned long long int mod_a = 981723817ll;
// unsigned long long int mod_b = 981534761ll;

/*
struct ll {
	unsigned long long a;
	unsigned long long b;

	ll() {}
	unsigned long long int cmp() {
		return (a << 31ll) | b;
	}

	bool operator==(ll oth) {
		return a == oth.a && b == oth.b;
	}

	ll operator *(ll oth) {
		oth.a *= a;
		oth.a %= mod_a;
		oth.b *= b;
		oth.b %= mod_b;
		return oth;
	}

	ll(char c) {
		return ll((unsigned long long)(c));
	}

	ll(int c) {
		return ll((unsigned long long)(c));
	}
		a = l % mod_a;
		a += mod_a;
		a %= mod_a;
		b = l % mod_b;
		b += mod_b;
		b %= mod_b;
	}

	ll operator +(ll oth) {
		oth.a += a;
		oth.a %= mod_a;
		oth.b += b;
		oth.b %= mod_b;
		return oth;
	}

	ll operator -(ll oth) {
		oth.a = mod_a + a - oth.a;
		oth.a %= mod_a;
		oth.b = mod_b + b - oth.b;
		oth.b %= mod_b;
		return oth;
	}
};
*/

ll base;
struct Conn {
	int to;
	char tag;
};

/*
ll invert(ll a) {
	ll res = a;
	for(int i = 0; i < 8; ++i) {
		res = res * (2 - res * a);
	}

	assert(res * a == 1);
	return res;
}
*/

// ll inv;

ll get_ash(string const &s) {
	ll ash(0);
	for(char c : s) {
		ash = ash * base;
		ash = ash + ll(c);
		// ash %= mod;
	}

	return ash;
}

int occur(vector<char> const &s, int len, ll ash) {
	// cerr << len << endl;
	// for(char c : s) cerr << c;
	// // cerr << endl;
	if(int(s.size()) < len) return 0;
	ll po(1);
	ll roll(0);
	for(int i = 0; i < len; ++i) {
		roll = roll * base;
		roll = roll + ll(s[i]);
		// roll %= mod;
		// roll += mod;
		// roll %= mod;
		po = po * base;
		// po %= mod;
	}

	// for(int i = -1; i < len; ++i) po = po * base;

	int total = 0;
	if(roll == ash) total++;
	for(int i = len; i < int(s.size()); ++i) {
		// cerr << roll << endl;
		roll = roll * base;
		roll = roll + ll(s[i]);
		roll = roll - ll(s[i-len]) * po;
		// roll %= mod;
		// roll += mod;
		// roll %= mod;
		if(roll == ash) total++;
		// cerr << roll.a << endl;
	}

	// cerr << "ot " << total << endl;
	return total;
}


struct Query {
	int node;
	ll ash;
};

vector<int> batch_queries(
		vector<vector<Conn>> const &tree,
		vector<Query> const &qs,
		vector<char> const &label,
		vector<vector<int>> const &dads) {

	int n = int(tree.size());
	vector<vector<pair<int, int>>> ata(n);
	unordered_map<unsigned long long int, int> useful;

	int cnt = 0;
	int index = 0;
	for(Query q : qs) {
		// if(!useful.count(q.ash.cmp())) useful[q.ash.cmp()] = ++cnt;
		if(!useful.count(q.ash)) useful[q.ash] = ++cnt;
		ata[q.node].push_back({useful[q.ash], index});
		++index;
	}

	vector<int> dp(cnt+1, 0);
	vector<int> res(qs.size());

	function<void(int, int)> dfs = [&](int node, int dad) {
		ll ash = 0;
		int len = 0;
		for(int i = node; i != 0 && len < 200; i = dads[i][0]) {
			ash = ash * base;
			ash = ash + ll(label[i]);
			// ash %= mod;
			// ash += mod;
			// ash %= mod;
			len++;
			// if(useful.count(ash.cmp())) dp[useful[ash.cmp()]]++;
			if(useful.count(ash)) dp[useful[ash]]++;
			// dp[useful[ash]]++;
		}
		for(auto p : ata[node]) {
			res[p.second] = dp[p.first];
		}
		for(Conn ch : tree[node]) if(ch.to != dad) {
			dfs(ch.to, node);
		}
		ash = 0;
		len = 0;
		for(int i = node; i != 0 && len < 200; i = dads[i][0]) {
			ash = ash * base;
			ash = ash + ll(label[i]);
			// ash %= mod;
			// ash += mod;
			// ash %= mod;
			len++;
			// dp[useful[ash]]--;
			// if(useful.count(ash.cmp())) dp[useful[ash.cmp()]]--;
			if(useful.count(ash)) dp[useful[ash]]--;
		}
	};

	for(int i : dp) assert(i == 0);

	dfs(0, 0);

	return res;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	base = ll(307ll);
	// ll h = get_ash("ca");
	// int u = occur({'c', 'a', 'c', 'a', 'a'}, 2, h);
	// cerr << "RHA " << h.a << " " << u << endl;
	// Input
	int n;
	cin >> n;

	// inv = invert(base);

	vector<vector<Conn>> tree(n);
	forn(lskdjf, n-1) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		string s;
		cin >> s;
		tree[a].push_back(Conn {b, s[0]});
		tree[b].push_back(Conn {a, s[0]});
	}

	// Dp
	vector<char> label(n, 'x');
	vector<vector<int>> dads(n);
	vector<bool> seen(n, false);
	vector<int> depths(n);
	function<void(int)> dfs0 = [&](int node) {
		assert(!seen[node]);
		seen[node] = true;
		for(Conn ch : tree[node]) if(!seen[ch.to]) {
			dads[ch.to].push_back(node);
			depths[ch.to] = depths[node] + 1;
			label[ch.to] = ch.tag;
			dfs0(ch.to);
		}
	};

	depths[0] = 0;
	dads[0].push_back(0);
	dfs0(0);

	// LCA
	const int LEVELS = 30;
	forn(l, LEVELS) {
		forn(i, n) dads[i].push_back(dads[dads[i][l]][l]);
	}

	auto goto_depth = [&](int node, int d) {
		forn(lala, LEVELS+1) {
			int l = LEVELS-lala;
			if(depths[dads[node][l]] >= d) node = dads[node][l];
		}
		return node;
	};

	auto lca = [&](int a, int b) {
		if(depths[a] > depths[b]) swap(a, b);
		b = goto_depth(b, depths[a]);
		if(a == b) return a;
		forn(lala, LEVELS+1) {
			int l = LEVELS-lala;
			if(dads[a][l] != dads[b][l]) {
				a = dads[a][l];
				b = dads[b][l];
			}
		}

		assert(dads[a][0] == dads[b][0]);
		return dads[a][0];
	};

	vector<Query> batch;

	struct Big_Query {
		int a;
		int b;
		int l;
		int len;
		ll ash;
		int index;
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
		// p.a = a;
		// p.b = b;
		ll ash = get_ash(s);
		p.ash = ash;
		reverse(s.begin(), s.end());
		ll rash = get_ash(s);
		p.index = int(batch.size());
		p.len = int(s.size());

		int l = lca(a, b);
		p.l = l;
		p.a = goto_depth(a, depths[p.l] + p.len);
		p.b = goto_depth(b, depths[p.l] + p.len);

		batch.push_back(Query {node : a, ash : ash});
		batch.push_back(Query {node : p.a, ash : ash});
		batch.push_back(Query {node : b, ash : rash});
		batch.push_back(Query {node : p.b, ash : rash});
		// batch.push_back(Query {node : v, ash : ash});
	}

	for(auto &v : dads) {
		while(v.size() > 1) v.pop_back();
		v.shrink_to_fit();
	}
	vector<int> res = batch_queries(tree, batch, label, dads);

	for(auto p : qs) {
		int total = res[p.index] - res[p.index + 1] + res[p.index + 2] - res[p.index + 3];
		// assert(at_depth(p.a, depths[p.l]) == p.l);
		// assert(at_depth(p.b, depths[p.l]) == p.l);
		vector<char> s;
		while(p.a != p.l) {
			// cerr << a << endl;
			// return 0;
			s.push_back(label[p.a]);
			p.a = dads[p.a][0];
		}
		// assert(s.size() <= p.len - 1);
		vector<char> sb;
		while(p.b != p.l) {
			sb.push_back(label[p.b]);
			p.b = dads[p.b][0];
		}
		// assert(sb.size() <= p.len - 1);
		reverse(sb.begin(), sb.end());
		for(int c : sb) s.push_back(c);

		// assert(s.size() <= 2*p.len - 2);
		// reverse(s.begin(), s.end());
		// cerr << "pr" << total << endl;
		total += occur(s, p.len, p.ash);
		cout << total << "\n";
	}
}
