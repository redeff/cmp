#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector<vector<double>> ns(n, vector<double>(k));
	for(int i = 0; i < n; ++i) for(int j = 0; j < k; ++j) cin >> ns[i][j];
	vector<double> sums(n, 0);
	for(int i = 0; i < n; ++i) for(int j = 0; j < k; ++j) sums[i] += ns[i][j];

	vector<double> probs(k);
	for(int i = 0; i < k; ++i) probs[i] = ns[0][i] / sums[0];
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < k; ++j) {
			double this_prob = ns[i][j] / sums[i];
			probs[j] = 1.0 / (1.0 + sums[i]) * probs[j] + sums[i] / (1.0 + sums[i]) * this_prob;
		}
	}

	cout << setprecision(12);
	for(double d: probs) cout << d << " ";
	// cout << cout.precision(12);
	cout << endl;
}
