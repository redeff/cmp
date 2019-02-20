#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll t;
	cin >> t;
	for(ll test = 0ll; test < t; ++test) {
		ll n;
		cin >> n;
		vector<ll> ns(n+1ll);
		ns[0ll] = 0ll;
		for(ll i = 0ll; i < n; ++i) {
			ll k;
			cin >> k;
			ns[i+1ll] = ns[i] + k;
		}

		ll ya, ma, da, ye, me, de;

		cin >> ya >> ma >> da >> ye >> me >> de;
		da--;
		de--;
		ma--;
		me--;
		da += ns[ma];
		de += ns[me];

		ll tim = (ye - ya) * ns[n];
		ya = 4ll * ((ya + 3ll) / 4ll);
		tim += (ye - ya + 3ll) / 4ll;
		cout << tim + (de - da) + 1ll << endl;
	}
}
