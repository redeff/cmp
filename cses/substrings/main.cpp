#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll mod = 1e9+7ll;

// Cantidad
vector<int> pref(string s) {
	int t = s.size();
	vector<int> res;
	for(int n = 1; n < s.size(); ++n) {
		for(int i = 0; i < t - n; ++i) {
			if(s[i] != s[n + i]) goto out;
		}
		res.push_back(n);
out:;
	}
	return res;
}

ll po(ll base, ll ex) {
	ll total = 1ll;
	while(ex) {
		if(ex&1) total = total * base % mod;
		base = base * base % mod;
		ex /= 2;
	}
	return total;
}

int main() {
	// assert(po(2, 5) == 32);
	const ll sigma = 'Z' - 'A' + 1;
	int n;
	cin >> n;
	string s;
	cin >> s;
	int m = s.size();
	auto pre = pref(s);

	// emp[i] = #strings de long. i tq no contengan a s
	vector<ll> emp(n+1);
	emp[0] = 1;

	// fre[i] = #strings de long. i tq si les apendo s,
	// en la string total s aparece solo una vez (al final)
	vector<ll> fre(n+1);
	fre[0] = 1;

	for(int i = 1; i <= n; ++i) {
		emp[i] = sigma * emp[i-1] % mod;
		if(i-m >= 0) emp[i] += mod - fre[i-m];
		emp[i] %= mod;

		fre[i] = emp[i];
		for(int p : pre) if(p <= i) {
			fre[i] += mod - fre[i-p];
			fre[i] %= mod;
		}
	}

	ll total = po(sigma, n) - emp[n] + mod;
	total %= mod;
	cout << total << endl;
	/*
	for(int i : pre) cerr << i << " ";
	cerr << endl << endl;
	vector<int> dp(n - m+1);
	for(int i = 0; i < n-m+1; ++i) {
		
	}
	ll total = 0;
	for(int i = 0; i + m <= n; ++i) {
		ll pr = po('Z' - 'A' + 1, i);
		for(int p : pre) {
			if(p <= i) pr = (pr + mod - po('Z' - 'A' + 1, i - p)) % mod;
		}
		total += pr * po('Z' - 'A' + 1, n - i - m) % mod;
		total %= mod;
		total += mod;
		total %= mod;
		cerr << i << " " << pr << endl;
	}

	cout << total << endl;
	*/
}
