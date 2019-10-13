#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;
typedef long long int ll;
ll inf = 333333333333;

int main() {
	int a, b, m, k;
	while(cin >> a >> b >> m >> k) {
		int n = a+b;
		vector<ll> cost(n);
		// D dps P
		forn(i, n) cin >> cost[i];
		vector<vector<int>> graph(n);
		forn(i, m) {
			int u, v;
			cin >> u >> v;
			--u; --v;
			v += a;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		struct Cmp {
			int as = 0;
			int bs = 0;
			ll cost = 0;
		};
		vector<Cmp> cmps(n, Cmp());
		vector<bool> seen(n, false);
		function<void(int, int)> dfs = [&](int node, int cmp) {
			if(seen[node]) return;
			seen[node] = true;
			cmps[cmp].cost += cost[node];
			if(node < a) cmps[cmp].as++;
			else cmps[cmp].bs++;
			for(int ch : graph[node]) dfs(ch, cmp);
		};
		forn(i, n) dfs(i, i);
		// cerr << "DFS" << endl;
		vector<ll> dp(n+1, inf);
		dp[0] = 0;
		for(Cmp c : cmps) {
			vector<ll> ndp(n);
			forn(j, n+1) {
				ndp[j] = inf;
				int as = j - c.as;
				if(as >= 0) ndp[j] = min(ndp[j], dp[as]);
				int bs = j - c.bs;
				if(bs >= 0) ndp[j] = min(ndp[j], c.cost + dp[bs]);
			}
			swap(ndp, dp);
		}
		/*
		forn(i, b-1) {
			assert(dp[a+i] <= dp[a+i+1]);
		}
		forn(i, a-1) {
			assert(dp[i] >= dp[i+1]);
		}
		*/
		// forn(i, n) cerr << dp[i] << " ";
		// cerr << endl;
		ll lo = 0;
		ll hi = 0;
		forn(i, n) {
			if(dp[i] <= k) {
				hi = max(hi, (ll)i);
				lo = max(lo, n-(ll)i);
			}
		}
		cout << hi << " " << lo << endl;
	}
}
