#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll MAX = 1000000000;

ll ask(ll a, ll b) {
	cout << "Q " << a << " " << b << endl;
	ll res;
	cin >> res;
	return res;
}

int main() {
	int test;
	cin >> test;
	for(int t = 0; t < test; ++t) {
		ll q00 = ask(0, 0);
		ll q10 = ask(MAX, 0);
		ll q01 = ask(0, MAX);

		ll le = ask(0, (MAX - q01 + q00)/2);
		ll lo = ask((MAX - q10 + q00)/2, 0);

		ll ri = MAX - q10 + lo;
		ll hi = MAX - q01 + le;

		cout << "A " << le << " " << lo << " " << ri << " " << hi << endl;

		cin >> q00;
		if(q00 < 1) return 0;
	}
}
