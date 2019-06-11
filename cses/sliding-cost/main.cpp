#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll gt(vector<ll> &ft, int node) {
	ll total = 0;
	for(int x = node; x; x -= x & -x) total += ft[x];
	return total;
}

void st(vector<ll> &ft, int node, ll delta) {
	for(int x = node; x < ft.size(); x += x & -x) ft[x] += delta;
}

int bin(vector<ll> &ft, ll val) {
	int lo = 0;
	int hi = ft.size();
	while(hi - lo > 1) {
		int mid = (hi + lo) / 2;
		if(gt(ft, mid) < val) lo = mid;
		else hi = mid;
	}

	return hi;
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	auto comp = ns;
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	vector<int> index(n);
	for(int i = 0; i < n; ++i) index[i] = lower_bound(comp.begin(), comp.end(), ns[i]) - comp.begin();

	vector<ll> used(1+n, 0);
	vector<ll> sums(1+n, 0);
	for(int i = 0; i < k; ++i) {
		st(used, 1+index[i], 1);
		st(sums, 1+index[i], ns[i]);
	}
	// cout << comp[bin(used, (k+1)/2)-1] << endl;
	// cerr << gt(sums, n) << endl;
	for(int i = -1; i+k < n; ++i) {
		if(i != -1) {
			st(used, 1+index[i], -1);
			st(used, 1+index[i+k],1);
			st(sums, 1+index[i], -ns[i]);
			st(sums, 1+index[i+k],ns[i+k]);
		}

		ll med = bin(used, (k+1)/2);
		ll lt = gt(used, med);
		ll lts = gt(sums, med);
		ll all = gt(sums, n);
		ll val = comp[med - 1];
		// cerr << lt << " " << lts << " " << all << " " << val << endl;

		ll cost = lt * val - lts + (all - lts) - (k - lt) * val;
		cout << cost << endl;
	}
}
