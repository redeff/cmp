#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n, x;
	cin >> n >> x;
	++x;

	vector<int> cs(n);
	for(int &i : cs) cin >> i;
	vector<int> ws(n);
	for(int &i : ws) cin >> i;

	vector<int> dp(x, 0);
	for(int b = 0; b < n; ++b) {
		for(int i = x-1; i - cs[b] >= 0; --i) {
			dp[i] = max(dp[i], dp[i - cs[b]] + ws[b]);
		}
	}

	cout << *max_element(dp.begin(), dp.end()) << endl;
}
