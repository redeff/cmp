#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

typedef long long int ll;
const ll n = 7;
const ll mod = 998244353;

int main() {
	int n;
	cin >> n;
	vector<ll> ns(n, 0);
	forn(i, 0, n) {
		cin >> ns[i];
	}

	ll total = 0;
	// forn(i, 0, n) forn(j, i+1, n) total += lcm(ns[i], ns[j]);
	forn(i, 0, n) forn(j, 0, n) total += ns[i] * ns[j];
	cout << total << endl;
}
