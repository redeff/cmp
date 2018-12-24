#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 333333333333;

ll to_start(ll d, ll x) {
	return (x+d-1)/d;
}

int main() {
	ll t;
	cin >> t;
	for(ll testcase = 0; testcase < t; ++testcase) {
		ll n, x, y, d;
		cin >> n >> x >> y >> d;
		x--;
		y--;
		n--;

		ll mn = INF;
		if(y % d == 0) {
			mn = min(mn, to_start(d, x) + to_start(d, y));
		}
		
		y = n - y;
		x = n - x;
		if(y % d == 0) {
			mn = min(mn, to_start(d, x) + to_start(d, y));
		}

		if((x - y) % d == 0) {
			mn = min(mn, abs(x - y) / d);
		}

		if(mn == INF) {
			cout << -1 << endl;
		} else {
			cout << mn << endl;
		}
	}
}

