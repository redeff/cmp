#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll mult(ll a, ll b, ll p) {
	if(b == 0) return 0;
	ll res = mult(a, b/2, p);
	res *= 2;
	res %= p;
	if(b % 2 == 1) res += a;
	res %= p;
	return res;
}

ll ex(ll n, ll e, ll p) {
	if(e == 0) return 1;
	ll res = ex(n, e/2, p);
	res = mult(res, res, p);
	// res %= p;
	if(e % 2 == 1) res = mult(res, n, p);
	// res %= p;
	return res;
}

ll inv(ll n, ll p) {
	return ex(n, p-2, p);
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int test;
	cin >> test;
	while(test --> 0) {
		ll n, p;
		cin >> n >> p;
		if(n >= p) {
			cout << 0 << endl;
		} else {
			ll total = p-1;
			for(ll k = p-1; k > n; --k) {
				total = mult(total, k, p);
			}
			cout << inv(total, p) << endl;
		}
	}
}
