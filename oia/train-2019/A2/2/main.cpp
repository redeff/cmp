#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	int n;
	cin >> n;

	vector<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];

	ll sum = accumulate(ns.begin(), ns.end(), 0ll);
	ll mx = *max_element(ns.begin(), ns.end());
	cout << 1 + 2 * mx - sum << endl;
}
