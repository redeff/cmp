#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll gcd (ll a, ll b) {
	if(a < b) swap(a, b);
	while (b) b ^= a ^= b ^= a %= b;
	return a;
}

ll lcd(ll a, ll b) {
	return (a * b) / gcd(a, b);
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, k;
	cin >> n >> k;

	ll total = 1;
	for(int i = 0; i < n; ++i) {
		ll c;
		cin >> c;
		total = lcd(total, c);
		total = gcd(total, k);
	}
	
	cout << (total == k ? "Yes" : "No") << endl;
}
