#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin >> n;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	nth_element(ns.begin(), ns.begin() + n/2, ns.end());
	ll total = 0;
	for(int i = 0; i < n; ++i) {
		total += abs(ns[i] - ns[n/2]);
	}

	cout << total << endl;
}
