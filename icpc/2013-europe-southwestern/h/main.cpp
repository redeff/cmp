#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 21092013ll;

int main() {
	int testcase;
	cin >> testcase;
	for(int test = 0; test < testcase; ++test) {
		vector<int> base;
		vector<int> then;
		string bases;
		string thens;
		cin >> bases >> thens;
		for(char c : bases) {
			if(c == 'U') {if(!base.empty()) base.pop_back();}
			else base.push_back(c == 'R' ? 0 : 2);
		}

		// cerr << "b" << base.size() << endl;
		// cerr << bases << endl;

		for(char c : thens) {
			if(c == 'U') then.push_back(1);
			else if(c == 'R') then.push_back(0);
			else then.push_back(2);
		}

		int n = thens.size();
		vector<int[3]> last(n + 1);
		last[n][0] = n;
		last[n][1] = n;
		last[n][2] = n;

		for(int i = n-1; i >= 0; --i) {
			for(int j = 0; j < 3; ++j) last[i][j] = last[i+1][j];
			last[i][then[i]] = i;
		}

		vector<ll> dp(n + 2);
		dp[n] = 1;
		dp[n+1] = 0;
		for(int i = n-1; i >= 0; --i) {
			dp[i] = (dp[last[i][0] + 1] + dp[last[i][2] + 1] + 1) % MOD;
		}

		ll total = dp[last[0][0] + 1] + dp[last[0][2] + 1] + 1;
		// cerr << total << endl;
		// cerr << dp[last[0][0] + 1] << endl;
		total %= MOD;
		int index = 0;
		while(!base.empty()) {
			// cerr << "AAA" << endl;
			index = last[index][1] + 1;
			if(index > n) break;
			// cerr << index << endl;
			total += dp[last[index][2 - base.back()] + 1] + 1;
			total %= MOD;
			base.pop_back();
		}
		cout << "Case " << test + 1 << ": " << total << endl;
	}
}
