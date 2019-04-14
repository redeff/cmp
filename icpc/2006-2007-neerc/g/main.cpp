#include <bits/stdc++.h>
using namespace std;

int d;
int fun(int k) {
	if(k <= d) return 0;
	return (k - 1 + d - 1 - 1) / (d - 1) - 1;
	// if(k <= d) return 0;
	/*
	else {
		int nxt = (k + d - 1) / d;
		return nxt + fun(nxt);
	}
	*/
}

int main() {
	// d = 5;
	// cerr << fun(26) << endl;
	int n;
	cin >> n >> d;
	vector<int> deg(n+1, 0);
	for(int i = 1; i <= n; ++i) {
		int k;
		cin >> k;
		deg[k]++;
	}

	int total = 0;
	for(int i : deg) total += fun(i);
	cout << total << endl;
}
