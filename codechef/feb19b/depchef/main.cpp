#include <bits/stdc++.h>
using namespace std;

int main() {
	int test;
	cin >> test;
	for(;test;test--) {
		int n;
		cin >> n;

		vector<int> a(n);
		vector<int> d(n);

		for(int i = 0; i < n; ++i) cin >> a[i];
		for(int i = 0; i < n; ++i) cin >> d[i];

		int mx = -1;

		for(int i = 0; i < n; ++i) {
			int nxt = (i + 1) % n;
			int prv = (i + n - 1) % n;

			if(d[i] > a[nxt] + a[prv]) mx = max(mx, d[i]);
		}

		cout << mx << endl;
	}
}
