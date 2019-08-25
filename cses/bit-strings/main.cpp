#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;

int main() {
	ll n;
	cin >> n;
	ll res = 1;
	while(n --> 0) {
		res *= 2;
		res %= mod;
	}
	cout << res << endl;
}
