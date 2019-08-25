#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll base;
vector<bool> poss;
ll can;
ll canz;

ll ex(ll b, ll e) {
	if(e == 0) return 1;
	return b * ex(b, e-1);
}

vector<ll> pasar(ll num) {
	vector<ll> total;
	while(num != 0) {
		total.push_back(num % base);
		num /= base;
	}

	// reverse(total.begin(), total.end());
	return total;
}

ll cosa(ll b, ll n) {
	if(b == 0) assert(false);
	if(n < 0) return 0;
	if(b == 1) return n+1;
	else return (ex(b, n+1) - 1) / (b-1);
}

ll rec(vector<ll> num, bool flag) {
	if(num.empty()) return 1;

	ll k = 0;
	for(ll i = 1; i < num.back(); ++i) {
		if(poss[i]) ++k;
	}

	ll total = 0;
	ll oth = poss[0] && num.back() != 0;
	total += (flag ? k : (k + oth)) * ex(can, int(num.size()) - 1);
	if(flag) {
		auto k = canz * cosa(can, int(num.size()) - 2);
		// cerr << "canz " << canz << endl;
		// cerr << "can " << can << endl;
		// cerr << "num " << nu,;
		// cerr << "K " << k << endl;
		total += k;
	}
	if(poss[num.back()]) {
		num.pop_back();
		total += rec(num, false);
	}

	return total;
}

ll caso(ll num, string s) {
	auto v = pasar(num);
	// vector<bool> 
	can = 0;
	canz = 0;
	poss = vector<bool>(s.size());
	for(int i = 0; i < s.size(); ++i) {
		poss[i] = s[i] == 'S';
		if(s[i] == 'S') {
			can++;
			if(i != 0) canz++;
		}
	}

	if(num == 0) return poss[0];
	return rec(v, true) + poss[0];
}

int main() {
	ll l, r;
	while(cin >> l >> r && r != -1) {
		// ll base;
		cin >> base;
		string p;
		cin >> p;
		cout << caso(r, p) - caso(l-1, p) << endl;
	}
}
