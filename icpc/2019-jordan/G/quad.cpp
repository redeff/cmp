#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
typedef long long int ll;
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<ll> as(n);
	vector<ll> bs(n);
	forn(i, n) cin >> as[i] >> bs[i];

	vector<bool> dead(n, false);

	int q;
	cin >> q;
	forn(asjfha, q) {
		int t;
		cin >> t;
		if(t == 1) {
			ll x;
			cin >> x;

			ll sum = 0;
			int killed = 0;
			int hungry = 0;
			forn(i, n) {
				sum += as[i];
				if(sum <= x) {
					if(x - sum > bs[i]) {
						if(!dead[i]) killed++;
						dead[i] = true;
						as[i] = 0;
					}
				} else {
					if(!dead[i]) hungry++;
				}
			}
			cout << killed << " " << hungry << endl;
		} else {
			ll a, b;
			int x;
			cin >> a >> b >> x;
			--x;
			as[x] = a;
			bs[x] = b;
			dead[x] = false;
		}
	}
}
