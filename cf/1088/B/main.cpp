#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll n, k;
	cin >> n >> k;

	vector<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];
	sort(ns.begin(), ns.end());
	reverse(ns.begin(), ns.end());

	ns.erase(unique(ns.begin(), ns.end()), ns.end());
	n = ns.size();

	ns.push_back(0);
	for(int i = n; i > 0; --i) {
		if(k == 0) break;
		else --k;
		cout << ns[i-1] - ns[i] << endl;
	}

	while(k > 0) {
		cout << 0 << endl;
		--k;
	}
}
