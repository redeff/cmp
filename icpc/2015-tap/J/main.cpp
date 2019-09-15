#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool game(vector<ll> ns) {
	sort(ns.begin(), ns.end());
	ll k = *min_element(ns.begin(), ns.end());
	if(k % (ns.size()+1) == 0) return false;

	k -= ns.size();
	for(ll i = 0; i < ns.size(); ++i) ns[i] -= i+1;
	ll q = *min_element(ns.begin(), ns.end());
	ll n = ns.size();
	if((n+1+k-1) / (n+1) != (n+1+q) / (n+1)) return true;
	else return 0;
}


int main() {
	ll n;
	cin.tie(0);
	ios::sync_with_stdio(0);
	while(cin >> n) {
		vector<ll> ns(n);
		for(ll &i : ns) cin >> i;
		if(game(ns)) cout << "S\n";
		else cout << "N\n";
	}
}
