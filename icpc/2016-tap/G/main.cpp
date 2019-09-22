#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef unsigned long long int ll;

const int lg = 100;

vector<int> base2(ll a) {
	// cerr << "A" << endl;
	vector<int> res;
	forn(laskdjf, lg) {
		// cerr << "." << endl;
		res.push_back(a % 2);
		a /= 2;
	}
	// cerr << "B" << endl;
	return res;
}

struct Trie {
	Trie *ch[2];
	Trie() {
		ch[0] = nullptr;
		ch[1] = nullptr;
	}
};

struct Conn {
	int to;
	ll wei;
};

int main() {
	int n;
	while(cin >> n) {
		Trie *tr = new Trie();
		// tr.emplace_back();

		function<void(Trie*, vector<int>&)> add = [&](Trie *trie, vector<int> &ns) {
			assert(trie != nullptr);
			if(ns.empty()) return;
			int last = ns.back();
			assert(last < 2);
			assert(0 <= last);
			ns.pop_back();
			if(trie->ch[last] == nullptr) {
				// tr.emplace_back();
				trie->ch[last] = new Trie();
			}

			add(trie->ch[last], ns);
		};

		function<void(Trie*, vector<int>&, ll&)> srch = [&](Trie *trie, vector<int> &ns, ll &l) {
			assert(trie != nullptr);
			if(ns.empty()) return;
			l *= 2;
			int last = ns.back();
			// cerr << last;
			assert(last < 2);
			assert(0 <= last);
			ns.pop_back();
			if(trie->ch[1-last] == nullptr) {
				last = 1-last;
			} else {
				l++;
			}
			srch(trie->ch[1-last], ns, l);
		};


		vector<vector<Conn>> graph(n);
		forn(lksdjf, n-1) {
			int a, b;
			ll wei;
			cin >> a >> b >> wei;
			--a; --b;
			graph[a].push_back(Conn {b, wei});
			graph[b].push_back(Conn {a, wei});
		}

		vector<ll> dp(n, 0);
		function<void(int, int, ll wei)> dfs = [&](int node, int dad, ll wei) {
			dp[node] = wei;
			auto tmp = base2(wei);
			add(tr, tmp);
			for(Conn ch : graph[node]) if(ch.to != dad) {
				dfs(ch.to, node, wei ^ ch.wei);
			}
		};

		dfs(0, 0, 0);

		forn(i, n) {
			ll res = 0;
			auto tmp = base2(dp[i]);
			srch(tr, tmp, res);
			cout << res << endl;
		}
	}
}
