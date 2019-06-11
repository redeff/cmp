#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ll;

// Ones in [0..n), and the number of ones in n
pair<ll, ll> f(ll n) {
	if(n == 0ull) return {0ull, 0ull};
	auto rec = f(n/10ull);

	return {
		10ull * rec.first + (n%10ull) * rec.second + (n+8ull)/10ull,
		rec.second + (n%10ull == 1ull)
	};
}

int main() {
	ll n;
	cin >> n;
	ll lo = 0;
	ll hi = 1;
	while(f(hi).first <= n) hi *= 2;
	while(hi - lo > 1) {
		ll mid = (hi + lo) / 2ull;
		if(f(mid).first <= n) lo = mid;
		else hi = mid;
	}

	cout << lo-1 << endl;
}
