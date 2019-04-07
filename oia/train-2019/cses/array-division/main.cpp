#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll n, k;
	cin >> n >> k;
	vector<ll> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];

	ll hi = accumulate(ns.begin(), ns.end(), 0ll);
	ll lo = *max_element(ns.begin(), ns.end()) - 1;
	while(lo + 1ll < hi) {
		ll mid = (hi + lo) / 2;
		ll block_sum = 0;
		ll num_blocks = 1;
		for(int i = 0; i < n; ++i) {
			block_sum += ns[i];
			if(block_sum > mid) {
				num_blocks++;
				block_sum = ns[i];
			}
		}
		if(num_blocks > k) lo = mid;
		else hi = mid;
	}

	cout << hi << endl;
}
