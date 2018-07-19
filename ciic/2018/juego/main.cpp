#include <bits/stdc++.h>
using namespace std;

int abs(int a) {
	return a < 0 ? -a : a;
}

int calc(vector<int> &ns, int n) {
	int total = 0;
	for(int i = 0; i < n; ++i) {
		total += abs(ns[i] + ns[i + n]);
	}
	return total;
}

int main() {
	int n;
	cin >> n;
	vector<int> ns(2 * n);
	for(int i = 0; i < 2 * n; ++i) cin >> ns[i];
	int total = calc(ns, n);
	for(int i = 0; i < n; ++i) ns[i] = -ns[i];
	total = max(total, calc(ns, n));
	cout << total << endl;
	return 0;
}
