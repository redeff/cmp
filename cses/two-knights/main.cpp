#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ll n;
	cin >> n;
	
	for(ll k = 1; k <= n; ++k) {
		ll total = (k*k) * (k*k - 1) / 2 - 4 * (k-1) * (k-2);
		cout << total << " ";
	}
	cout << endl;
}
