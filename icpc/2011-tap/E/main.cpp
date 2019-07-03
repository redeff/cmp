#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	while(cin >> n && n != -1) {
		vector<ll> ns(n-1);
		for(ll &i : ns) cin >> i;
		sort(ns.begin(), ns.end());

		unordered_set<ll> sets;
		for(ll i : ns) sets.insert(i);

		ll sum = 0;
		for(ll i : ns) sum += i;

		int a = (n-1) / 2;
		int b = (n-3) / 2;

		int total = 0;
		ll l = n * ns[a] - sum;
		// cerr << n <<" "<< a <<" "<<  ns[a] <<" "<< sum << " " << l << endl;
		if(l > ns[a] && 0 == sets.count(l)) total++;
		l = n * ns[b] - sum;
		if(l < ns[b] && 0 == sets.count(l)) total++;

		l = sum/(n-1);
		if(sum % (n-1) == 0 && 0 == sets.count(l) && ns[a] > l && ns[b] < l)
			total++;
		cout << total << "\n";
	}
}
