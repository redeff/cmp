#include <bits/stdc++.h>
using namespace std;

int t = 'Z' - 'A' + 1;

class OrderlyString {
public:
	int longestLength(string s) {
		int n = s.size();
		vector<int> v(n);
		for(int i = 0; i < n; ++i) v[i] = s[i] - 'A';

		vector<int> dp(t, 0);
		for(int i : v) {
			dp[i] = 1 + *max_element(dp.begin(), dp.begin() + i + 1);
		}

		return *max_element(dp.begin(), dp.end());
	}
};

