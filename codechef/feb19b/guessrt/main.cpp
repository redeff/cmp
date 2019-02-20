#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 1000000007ll;

ll ex(ll base, ll exponent) {
	exponent %= MOD - 1;
	exponent += MOD - 1;
	exponent %= MOD - 1;

	ll curr = 1;
	while(exponent > 0) {
		if(exponent % 2 == 1) {
			curr *= base;
			curr %= MOD;
		}
		exponent /= 2ll;
		base *= base;
		base %= MOD;
	}

	return curr;
}

int main() {
	int t;
	cin >> t;
	for(;t;t--) {
		ll n, k, m;
		cin >> n >> k >> m;
		
		ll out = 1;
		ll times = (m + 1) / 2;
		out *= ex(n - 1, times);
		out %= MOD;
		out *= ex(n, -times);
		out %= MOD;

		if(m % 2 == 0) {
			out *= n + k - 1;
			out %= MOD;
			out *= ex(n + k, -1);
			out %= MOD;
		}

		out = 1 - out + MOD;
		out %= MOD;
		cout << out << endl;
	}
}
