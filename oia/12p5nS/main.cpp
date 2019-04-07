#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream cin("oficinas.in");
	ofstream cout("oficinas.out");
	int n;
	cin >> n;
	vector<pair<int, int>> ns(n);
	for(auto &i : ns) cin >> i.first >> i.second;
	sort(ns.begin(), ns.end());
	vector<int> sums(n+1);
	sums[0] = 0;
	for(int i = 0; i < n; ++i) sums[i+1] = ns[i].second + sums[i];

	struct Dp {
		int best;
		int root;
	};

	vector<vector<Dp>> dp(n+1);
	dp[0] = vector<Dp>(n+1, Dp {0, -1});

	typedef pair<int, int> pii;
	function<pair<pii, pii>(pii, int)> split = [&](pii p, int k) -> pair<pii, pii> {
		assert(p.first <= k || p.first + p.second > k);
		return {{p.first, k - p.first}, {k+1, p.second+p.first-k-1}};
	};

	for(int len = 1; len <= n; ++len) {
		dp.emplace_back();
		for(int a = 0; a + len <= n; ++a) {
			dp[len].push_back(Dp {99999999, -1});
			for(int k = a; k < a + len; ++k) {
				auto p = split({a, len}, k);
				auto p1 = p.first;
				auto p2 = p.second;
				int cost = dp[p1.second][p1.first].best
					+ dp[p2.second][p2.first].best
					+ sums[a+len] - sums[a];
				if(cost < dp[len][a].best) {
					dp[len][a].best = cost;
					dp[len][a].root = k;
				}
			}
		}
	}

	function<void(pii)> display = [&](pii p) {
		int root = dp[p.second][p.first].root;
		if(root == -1) return;
		auto pr = split(p, root);
		cout << "(";
		display(pr.first);
		cout << ns[root].first;
		display(pr.second);
		cout << ")";
	};

	cout << dp[n][0].best << endl;
	display({0, n});
	cout << endl;
}
