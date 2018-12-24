#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll n;
	cin >> n;
	vector<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];
	
	cout << n + 1 << endl;

	ll sum = 0;
	for(ll i = n - 1; i >= 0; --i) {
		ll delta = i - (ns[i] + sum);
		delta %= n;
		delta += n;
		delta %= n;
		cout << 1 << " " << i + 1 << " " << delta << endl;
		sum += delta;
		sum %= n;
	}

	cout << 2 << " " << n << " " << n << endl;
	
}
