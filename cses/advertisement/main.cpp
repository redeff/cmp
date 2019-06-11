#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector<int> prvs(vector<ll> ns) {
	int n = ns.size();
	vector<int> res(n);
	for(int i = 0; i < n; ++i) {
		int k = i-1;
		while(k != -1 && ns[k] >= ns[i]) k = res[k];
		res[i] = k;
	}

	return res;
}

int main() {
	int n;
	cin >> n;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	auto f = prvs(ns);
	reverse(ns.begin(), ns.end());
	auto b = prvs(ns);
	reverse(b.begin(), b.end());
	for(int &i : b) i = n - i - 1;
	reverse(ns.begin(), ns.end());

	ll total = 0;
	for(int i = 0; i < n; ++i) {
		total = max(total, ns[i] * (ll)(b[i] - f[i] - 1));
	}
	cout << total << endl;
}
