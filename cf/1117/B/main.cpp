#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];
	sort(ns.begin(), ns.end());
	reverse(ns.begin(), ns.end());

	ll total = m * ns[0];
	total -= (m/(k+1)) * (ns[0] - ns[1]);

	cout << total << endl;
}
