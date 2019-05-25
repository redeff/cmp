#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7;

int main() {
	int n;
	cin >> n;

	vector<ll> ns;
	ll fact = 1;
	while(ns.size() < n) {
		// cerr << ns.size() << ": ";
		// for(ll i : ns) cerr << i << " ";
		// cerr << endl;

		vector<ll> ms(ns.size() + 1);
		fact *= ms.size();
		fact %= mod;
		ll sum = 0;
		ll acc = 0;
		for(int i = ns.size() - 1; i >= 0; --i) {
			sum += ns[i];
			sum %= mod;
			ms[i] = sum * 2ll % mod;
			if(i - 1 >= 0) ms[i] += ns[i-1];
			ms[i] %= mod;
			acc += ms[i];
			acc %= mod;
		}
		ms.back() = mod + fact - acc;
		ms.back() %= mod;
		swap(ms, ns);
	}
	/*
	cerr << ns.size() << ": ";
	for(ll i : ns) cerr << i << " ";
	cerr << endl;
	*/

	// for(ll i : ns) cerr <<
	cout << ns.back() << endl;
}
