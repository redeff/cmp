#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll mod = 1ll << 62ll;

vector<ll> pass(vector<ll> ns, ll k) {
	int n = int(ns.size());
	for(int i = 1; i < n; ++i) {
		ns[i] += ns[i-1]*k;
		ns[i] %= mod;
	}
	return ns;
	/*
	if(flag) {
		reverse(ns.begin(), ns.end());
		ns.pop_back();
		reverse(ns.begin(), ns.end());
	}
	*/
}

ll sum(vector<ll> const &ns) {
	ll s = 0;
	for(ll i : ns) {
		s += i;
		s %= mod;
	}
	return s;
}

int sigma = 'z' - 'a' + 1;
ll diff_til_repeat(string s) {
	int n = int(s.size());
	vector<bool> used(sigma, false);
	for(int i = 0; i < n; ++i) {
		if(used[s[i]]) return i;
		used[s[i]] = true;
	}
	return n;
}



int main() {
	ll n;
	cin >> n;
	string s;
	cin >> s;

	ll k = diff_til_repeat(s);
	assert(k <= sigma);
	cout << k << endl;

	vector<ll> dp(n+1, 0);
	dp.front() = 1;

	ll total = 0;
	for(int i = k-1; i >= 0; --i) {
		cout << "A ";
		for(ll i : dp) cout << i << " ";
		cout << endl;
		dp = pass(dp, sigma-i);
		dp.pop_back();
		cout << "P ";
		for(ll i : dp) cout << i << " ";
		cout << endl;
		if(i%2 != k%2) {
			for(ll i : pass(dp, sigma)) cout << i << " ";
			cout << endl;
			total += sum(pass(dp, sigma));
			total %= mod;
		}
	}

	cout << total << endl;
}
