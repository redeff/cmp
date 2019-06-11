#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
int main() {
	ll n;
	cin >> n;
	ll total = n * (n+1) / 2;
	for(int i = 0; i < n-1; ++i) {
		ll a;
		cin >> a;
		total -= a;
	}

	cout << total << endl;
}
