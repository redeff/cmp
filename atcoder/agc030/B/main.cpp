#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll l;

ll dist(ll a, ll b) {
	if(a < b) return b - a;
	else return l + b - a;
}

int main() {
	ll n;
	cin >> l >> n;

	deque<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];
	sort(ns.begin(), ns.end());

	ll curr = 0;
	ll total = 0;
	while(!ns.empty()) {
		ll dist1 = dist(curr, ns.front());
		ll dist2 = dist(ns.back(), curr);

		total += max(dist1, dist2);
		if(dist1 < dist2) {
			curr = ns.back();
			ns.pop_back();
		} else {
			curr = ns.front();
			ns.pop_front();
		}
	}

	cout << total << endl;
}
