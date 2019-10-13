#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;
typedef long long int ll;

ll mx(ll bud, ll sum) {
	if(sum+1 > bud) return 0;
	ll res = 1;
	forn(i, 4) {
		if(sum + 10*res <= bud) res *= 10;
	}
	return res;
}

int main() {
	int n, m;
	while(cin >> n >> m) {
		ll total = 0;
		forn(lkshfaksjf, m) {
			ll bud;
			cin >> bud;
			ll curr;
			cin >> curr;
			ll sum = 0;
			forn(i, n-1) {
				ll t;
				cin >> t;
				sum += t;
			}
			total += mx(bud, sum);
			if(sum + curr <= bud) total -= curr;
		}
		cout << total << endl;
	}
}
