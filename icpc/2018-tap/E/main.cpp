#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const int bound = 1001;
ld dp[bound][bound][2];
ld prob[bound][bound];

ld inf = 33333333333333.0;

int main() {
	int n;
	cin >> n;

	vector<ld> as(n);
	vector<ld> bs(n);
	for(ld &f : as) cin >> f;
	reverse(as.begin(), as.end());
	for(ld &f : bs) cin >> f;

	prob[0][0] = 0;
	dp[0][0][0] = 0;
	dp[0][0][1] = 0;
	for(int i = 0; i <= n; ++i) for(int j = 0; j <= n; ++j) {
		if(i != 0 || j != 0) {
			prob[i][j] = j == 0 ? prob[i-1][j] + as[i-1] : prob[i][j-1] + bs[j-1];

			dp[i][j][0] = inf;
			dp[i][j][1] = inf;

			if(i > 0) {
				dp[i][j][0] = dp[i-1][j][0] + (i+j) * as[i-1];
			}

			if(j > 0) {
				dp[i][j][1] = dp[i][j-1][1] + (i+j) * bs[j-1];
			}

			for(int k = 0; k < 2; ++k) {
				dp[i][j][k] = min(dp[i][j][k], (1.0 - prob[i][j]) * (i+j) + dp[i][j][1-k]);
			}
		}
	}

	cout << setprecision(6) << fixed;
	cout << min(dp[n][n][0], dp[n][n][1]) << endl;
}
