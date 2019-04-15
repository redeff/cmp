#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

pair<ll, ll> doit(ll n, ll k, ll m) {
	ll total = n + m;
	ll add = 0ll;
	ll c = 0ll;

	// c = c + k*s
	// total = total - s
	// c + k*s <= total-s - 1
	// k*s + s < total - c - 1
	// (k+1) * s < total - c - 1
	// s <= (total - c - 1) / (k + 1)
	while(total > n) {
		{ // Slow
			total -= 1ll;
			if(c == 0ll) add++;
			c += k;
			c %= total;
		}
		{ // Fast
			ll s = (total - c - 1ll) / (k + 1ll);
			s = min(s, total - n);
			if(s != 0ll) {
				if(c == 0ll) add++;
				total -= s;
				c += k * s;
				assert(c < total);
				assert(c > 0ll);
				assert(total >= n);
			}
		}
	}

	return {add, c};
}

int main() {
	ll n, k, m;
	cin >> n >> k >> m;
	string s;
	cin >> s;
	auto p = doit(n, k, m);
	cerr << (char) ((s[p.second] + p.first - 'A') % 26 + 'A') << endl;
}
