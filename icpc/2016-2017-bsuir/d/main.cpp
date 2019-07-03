#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll inv(vector<ll> &ns) {
	int n = int(ns.size());
	if(n == 1 || n == 0) return 0;
	int k = n/2;

	vector<ll> as;
	vector<ll> bs;

	for(int i = 0; i < n; ++i)
		if(i < k) as.push_back(ns[i]);
		else bs.push_back(ns[i]);

	ll total = 0;
	total += inv(as);
	total += inv(bs);

	int a = 0;
	int b = 0;
	while(a < int(as.size()) || b < int(bs.size())) {
		if(a == int(as.size())) {
			ns[a+b] = bs[b];
			++b;
		}
		else if(b == int(bs.size())) {
			ns[a+b] = as[a];
			++a;
			total += bs.size() - b;
		}
		else if(as[a] < bs[b]) {
			ns[a+b] = as[a];
			++a;
			total += bs.size() - b;
		}
		else if(as[a] >= bs[b]) {
			ns[a+b] = bs[b];
			++b;
		}
	}
	return total;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	ll p, q;
	cin >> p >> q;

	string s;
	cin >> s;
	int n = int(s.size());
	vector<ll> ns(n+1);
	ns[0] = 0;
	for(ll i = 0; i < n; ++i) {
		ns[i+1] = ns[i] - p;
		if(s[i] - '0') ns[i+1] += q;
	}

	cout << inv(ns) << "\n";
}
