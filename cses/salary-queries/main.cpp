#include <bits/stdc++.h>
using namespace std;

typedef int ll;

const ll BOUND = 1e6;
// const ll LBOUND = 1e6;

// unordered_map<ll, ll> ft;
int ft[BOUND];
vector<ll> coord;

void ft_set(ll node, ll delta) {
	node = lower_bound(coord.begin(), coord.end(), node) - coord.begin();
	node += 10;
	for(ll x = node; x < BOUND; x += x & -x) {
		ft[x] += delta;
	}
}

ll ft_get(ll node) {
	node = lower_bound(coord.begin(), coord.end(), node) - coord.begin();
	node += 10;
	ll total = 0;
	for(ll x = node; x; x -= x & -x) {
		total += ft[x];
	}
	return total;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<ll> ns(n);
	for(ll &i : ns) {
		cin >> i;
		coord.push_back(i);
	}

	vector<tuple<bool, ll, ll>> quer;
	for(int i = 0; i < q; ++i) {
		string t;
		ll a, b;
		cin >> t >> a >> b;

		if(t == "!") {
			coord.push_back(b);
			quer.emplace_back(true, a, b);
		} else {
			coord.push_back(a-1);
			coord.push_back(b);
			quer.emplace_back(false, a, b);
		}
	}

	sort(coord.begin(), coord.end());
	coord.erase(unique(coord.begin(), coord.end()), coord.end());

	for(int i : ns) {
		ft_set(i, 1);
	}

	for(auto p : quer) {
		ll a = get<1>(p);
		ll b = get<2>(p);

		if(get<0>(p)) {
			ft_set(ns[a-1], -1);
			ft_set(b, 1);
			ns[a-1] = b;
		} else {
			cout << ft_get(b) - ft_get(a-1) << "\n";
		}
	}
}
