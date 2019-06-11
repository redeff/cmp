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
	for(int i = 0; i < k; ++i) st(used, 1+index[i], 1);
	cout << comp[bin(used, (k+1)/2)-1] << endl;
	for(int i = 0; i+k < n; ++i) {
		st(used, 1+index[i], -1);
		st(used, 1+index[i+k],1);
		cout << comp[bin(used, (k+1)/2)-1] << endl;
	}
}
