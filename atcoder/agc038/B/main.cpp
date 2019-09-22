#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

typedef long long int ll;

int main() {
	ll n, k;
	cin >> n >> k;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<int> prv(n);
	forn(i, 0, n) {
		ll p = i-1;
		while(p != -1 && ns[p] < ns[i]) p = prv[p];
		prv[i] = p;
	}

	vector<int> nxt(n);
	forn(j, 0, n) {
		ll i = n-j-1;
		ll p = i+1;
		while(p != n && ns[p] > ns[i]) p = nxt[p];
		nxt[i] = p;
	}

	ll total = 0;
	ll grow = 0;
	vector<bool> inc(n);
	forn(i, 0, n) {
		if(i > 0 && ns[i-1] < ns[i]) grow++;
		else grow = 1;
		if(grow >= k) {
			total = 1;
			inc[i] = true;
		}
	}

	forn(i, k-1, n) {
		if(inc[i]) continue;
		if(i == k-1) {
			total++;
			continue;
		}
		if(i - prv[i] >= k && nxt[i-k] - (i-k) >= k) continue;
		total++;
	}
	cout << total << endl;
}
