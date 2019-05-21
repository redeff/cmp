#include <bits/stdc++.h>
using namespace std;

typedef long long unsigned int ll;

/*
ll inv(ll a) {
	assert(a & 1ull);

	ll x = 1ull;
	for(int i = 0; i < 6; ++i) x = 2ull * x - a * x * x;

	assert(a * x == 1ull);
	return x;
}
*/

/*
ll po(ll b, ll e) {
	ll res = 1ull;
	while(e) {
		if(e & 1) res *= b;
		b *= b;
		e /= 2ull;
	}

	// cerr << res << endl;

	return res;
}
*/

// ll base = 74839402946758471ull;
ll base;
// ll inv_base;

vector<ll> hashes(string s) {
	int n = (int)s.size();
	vector<ll> res(n+1);
	res[0] = 0;
	for(int i = 0; i < n; ++i) {
		res[i+1] = res[i] * base + (ll)(s[i] - 'a' + 1);
	}

	return res;
}

vector<ll> pos;
ll of_range(vector<ll> &hsh, int a, int b) {
	return hsh[b] - hsh[a] * pos[b - a];
}

bool is_palindrome(int n, vector<ll> &hsh, vector<ll> &rhsh, int a, int b) {
	return of_range(hsh, a, b) == of_range(rhsh, n - b, n - a);
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	string s;
	cin >> s;
	int n = (int)s.size();

	base = 7483940294678471ull;
	pos = vector<ll>(n + 10);
	pos[0] = 1ull;
	for(int i = 1; i < pos.size(); ++i) pos[i] = pos[i-1] * base;
	// inv_base = inv(base);

	vector<ll> hsh = hashes(s);
	reverse(s.begin(), s.end());
	vector<ll> rhsh = hashes(s);
	reverse(s.begin(), s.end());

	int a = 0, b = 0;
	int len = 0;
	for(int i = 0; i < 2*n; ++i) {
		int lo = max(0, i - n) - 1;
		int hi = i / 2;
		while(hi - lo > 1) {
			int mid = (hi + lo) / 2;
			if(is_palindrome(n, hsh, rhsh, mid, i - mid)) hi = mid;
			else lo = mid;
		}

		if(len < i - hi - hi) {
			len = i - hi - hi;
			a = hi;
			b = i - hi;
		}
	}

	for(int i = a; i < b; ++i) cout << s[i];
	cout << "\n";
}
