#include <bits/stdc++.h>
using namespace std;

#define SIZE 2000000100

typedef long long int ll;

ll choose(ll a) {
	return (a * (a - 1)) / 2;
}

int main() {
	int n;
	cin >> n;

	unordered_map<ll, ll> xs;
	unordered_map<ll, ll> ys;
	unordered_map<ll, ll> both;

	for(int i = 0; i < n; ++i) {
		ll x, y;
		cin >> x >> y;
		ll ha = x + y * SIZE;
		xs[x]++;
		ys[y]++;
		both[ha]++;
	}

	ll total = 0;
	for(auto x : xs) total += choose(x.second);
	for(auto y : ys) total += choose(y.second);
	for(auto z : both) total -= choose(z.second);

	cout << total << endl;
}
