#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long int ll;

ll bound = 100000;
 
int main() {
	ll d, m, a, n, b;
	cin >> d >> m >> a >> n >> b;

	for(ll i = 0; i < n+m; ++i) {
		assert(i < bound);
		ll l = i < m ? a : b;

		if(l <= d) break;
		if(2*d <= l) {
			cout << i+1 << endl;
			return 0;
		} else {
			d = 2*d - l;
			// d = 2^n * d - (2^n - 1) * l
		}
	}
	cout << -1 << endl;
}
