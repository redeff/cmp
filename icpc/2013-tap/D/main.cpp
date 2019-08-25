#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, f;
	cin >> n >> f;

	vector<ll> ns(n);
	{
		ll a, b, c;
		cin >> a >> b >> c;
		ns[0] = a;
		for(ll i = 1; i < n; ++i) {
			ns[i] = (b * ns[i-1] + c) % f;
		}
	}

	vector<set<ll>> sets(f);

	for(int i = 0; i < n; ++i) {
		sets[ns[i]].insert(i);
		sets[ns[i]].insert(i+n);
	}

	ll m;
	cin >> m;
	for(ll q = 0; q < m; ++q) {
		ll i, t;
		cin >> i >> t;
		--i;
		sets[ns[i]].erase(i);
		sets[ns[i]].erase(i+n);
		ns[i] = t;
		sets[t].insert(i);
		sets[t].insert(i+n);
		ll left = *next(sets[t].find(i)) - i;
		ll right = n + i - *prev(sets[t].find(i+n));
		cout << right << " " << left << "\n";
	}
}
