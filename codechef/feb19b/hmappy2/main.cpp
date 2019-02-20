#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll gcd(ll a, ll b) {
	if(a < b) swap(a, b);
	if(b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	int test;
	cin >> test;
	for(;test;test--) {
		ll n, a, b, k;
		cin >> n >> a >> b >> k;
		ll total = n/a + n/b - 2ll * (n/(a*b/gcd(a, b)));
		cout << (total < k ? "Lose" : "Win") << endl;
	}
}
