#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef long long int ll;

ll gcd(ll a, ll b) {
	while(b != 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

bool caso() {
	ll n, k;
	cin >> n >> k;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	ll d = gcd(k, n);
	ll sum = 0;

	forn(i, d) {
		ll mx = 0;
		ll c = 0;

		forn(j, n/d) {
			ll pos = (i + j*k) % n;

			if(pos < k) sum += c;

			c -= ns[pos] - ns[(pos + 1)%n];
			mx = max(mx, -c);
		}

		if(c != 0) return false;
		sum += mx*(k/d);
	}

	return sum <= ns[0] && (ns[0] - sum) % (k/d) == 0;
}

int main() {
	cout << (caso() ? "S" : "N") << endl;
}
