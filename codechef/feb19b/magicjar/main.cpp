#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int test;
	cin >> test;
	for(;test; test--) {
		ll n;
		cin >> n;
		ll total = 0;
		for(int i = 0; i < n; ++i) {
			ll a;
			cin >> a;
			total += a - 1;
		}
		cout << total + 1 << endl;
	}
}
