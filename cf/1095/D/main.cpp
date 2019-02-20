#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct TwoSet {
	ll a;
	ll b;
};

bool contains(ll t, TwoSet s) {
	return s.a == t || s.b == t;
}

int main() {
	ll n;
	cin >> n;
	vector<TwoSet> ns(n);
	for(ll i = 0; i < n; ++i) {
		cin >> ns[i].a >> ns[i].b;
		ns[i].a --;
		ns[i].b --;
	}

	if(n == 3) {
		cout << "1 2 3 " << endl;
	} else {

		vector<ll> order {0};
		for(ll i = 0; i < n - 1; ++i) {
			ll last = order.back();
			TwoSet s = ns[last];
			if(contains(s.a, ns[s.b])) {
				order.push_back(s.b);
			} else {
				order.push_back(s.a);
			}
		}

		for(ll i : order) cout << i + 1 << " ";
		cout << endl;
	}
}
