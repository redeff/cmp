#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;

	long long ns[n], dp[n] = {0};
	for(auto &i : ns) cin >> i;

	for(int l = 0; l < n; ++l) for(int i = 0; i < n-l; ++i)
		dp[i] = l%2
			? max(dp[i] + ns[i+l], dp[i+1] + ns[i])
			: min(dp[i], dp[i+1]);

	cout << dp[0] << endl;
}
