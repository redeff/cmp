#include <bits/stdc++.h>
using namespace std;

int calc(vector<int> ns) {
	int n = int(ns.size());

	int diff = 0;
	int mult = 0;
	for(int i : ns) {
		if(i > 0) diff++;
		if(i > 1) mult++;
	}
	assert(mult <= diff);
	assert(diff <= n);

	if(diff == 1) return 1;
	if(diff == n) return 0;
	if(diff == 2) return n - 2 + mult;
	if(diff >= 3) return n - (n == 4 && mult == 0);

	assert(false);
}
int main() {
	int s, n;
	cin >> s >> n;

	vector<int> ns(n, 0);
	for(int i = 0; i < s; ++i) {
		int a;
		cin >> a;
		ns[a-1]++;
	}

	cout << calc(ns) << endl;
}
