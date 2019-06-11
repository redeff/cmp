#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

// #1s in [0..n), #1s in n
pair<ll, ll> f(ll n) {
	if(n == 0) return {0, 0};
	auto rec = f(n/2);
	return {n/2 + 2 * rec.first + (n%2) * rec.second, rec.second + n%2};
}

int main() {
	ll n;
	cin >> n;
	auto p = f(n+1);
	cout << p.first << endl;
}
