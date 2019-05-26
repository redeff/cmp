#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	string s;
	cin >> s;

	int n = (int) s.size();
	vector<int> dp(n, 0);
	for(int i = 1; i < n; ++i) {
		int t = i-1;
		while(s[i] != s[dp[t]]) {
			t = dp[t]-1;
			if(t == -1) break;
		}

		if(t == -1) dp[i] = 0;
		else dp[i] = dp[t]+1;
	}

	for(int i = 0; i < dp.back(); ++i) cout << s[i];
	cout << "\n";
	// cout << dp.back() << endl;
}
