#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7;

ll po(ll b, ll e) {
	ll r = 1;
	while(e) {
		if(e&1) r = r * b % mod;
		b = b * b % mod;
		e /= 2;
	}

	return r;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		ll a, b;
		cin >> a >> b;
		cout << po(a, b) << "\n";
	}
}
