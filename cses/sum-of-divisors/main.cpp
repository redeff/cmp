#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7;

ll gauss(ll a, ll b) {
	return (a + b) % (2ll * mod) * ((a - b + 1) % (2ll * mod)) / 2ll % mod;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	ll n;
	cin >> n;
	ll lo = n+1;
	ll total = 0;

	for(ll k = 1; k*k < n; ++k) {
		ll a = n / k;
		ll b = n / (k+1) + 1;
		lo = b;

		total += gauss(a, b) * k;
		total %= mod;
	}

	for(ll i = 1; i < lo; ++i) {
		total += n / i * i;
		total %= mod;
	}

	cout << total << "\n";
}
