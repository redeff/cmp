#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, m;
	while(cin >> n >> m && n != -1) {
		vector<ll> ns(n);
		for(ll &i : ns) cin >> i;
		for(int i = 1; i < n; ++i) {
			ns[i] += ns[i-1];
		}

		ll total = 0;
		for(ll i : ns) total += i;
		cout << total * m << "\n";
	}
}
