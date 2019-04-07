#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Opt {
	ll rest;
	ll divi;
};

vector<Opt> jumps(vector<ll> &ns, ll n, ll k) {
	vector<Opt> jump(n);

	ll all = accumulate(ns.begin(), ns.end(), 0ll);

	ll sum = k/all*all;
	Opt b = {k/all, 0};

	for(ll i = 0; i < n; sum -= ns[i], ++i) {
		while(sum + ns[b.divi] <= k) {
			sum += ns[b.divi];
			b.divi++;
			if(b.divi == n) b.divi = 0, b.rest++;
		}
		jump[i] = b;
	}

	return jump;
}

int main() {
	ll n, k;
	cin >> n >> k;

	vector<ll> ns(n);
	for(ll i = 0; i < n; ++i) cin >> ns[i];

	vector<Opt> jump = jumps(ns, n, k);

	function<Opt(Opt)> go = [&](Opt a) {
		return Opt {jump[a.divi].rest + a.rest, jump[a.divi].divi};
	};

	Opt a = Opt {0, 0};
	Opt b = go(a);
	ll i = 1;
	while(a.divi != b.divi) {
		a = go(a);
		b = go(go(b));
		++i;
	}

	ll turns = b.rest - a.rest;
	cout << (i + turns - 1) / turns << endl;

}
