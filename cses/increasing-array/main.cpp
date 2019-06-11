#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin >> n;

	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	ll mx = 0;
	ll total = 0;
	for(ll i : ns) {
		total += max(mx - i, 0ll);
		mx = max(mx, i);
	}
	cout << total << endl;
}
