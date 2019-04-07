#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll g(int i, bool b) {
	if(i == 0) return !b;
	if(i % 2 == 0) {
		if(b == false) {
			return g(i-1, false) * 3 + g(i-1, true) * 2;
		} else {
			return g(i-1, false) * 2 + g(i-1, true) * 3;
		}
	} else {
		if(b == false) {
			return g(i-1, false) * 5;
		} else {
			return g(i-1, true) * 5;
		}
	}
}

ll f(ll n, bool b) {
	if(n == 0) return !b;
	ll p = 1ll;
	int i = -1;
	int rec = b;
	while(p <= n) p *= 5ll, rec = !rec, i++;
	rec = !rec;
	p /= 5ll;

	// if(p == 1) return f(n - p, rec) + (rec + 1) / 2;
	// return f(n - p, rec) + (p + rec * p/5) / 2;
	return f(n - p, rec) + g(i, b);
}

int main() {
	ll n;
	while(cin >> n &&  n != -1) {
		cout << f(n, false) << endl;
	}
}
