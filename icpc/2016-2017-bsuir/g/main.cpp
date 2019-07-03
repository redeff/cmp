#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll n; ll k;

double nxt(double p) {
	double t = floor(p);
	return t / double(k) * p + (double(k) - t) * (double(k) + t + 1.0) / (2.0 * double(k));
}

int main() {
	cin >> n >> k;
	double p = (double(k) + 1.0) / 2.0;
	ll i = 1;
	for(; i < n; ++i) {
		if(floor(p) >= k-1) {
			ll d = n - i;

			double h = (double(k) - 1) / double(k);
			double hd = pow(h, d);
			p =  hd * p + (hd - 1.0) / (h - 1.0);
			break;
		}
		p = nxt(p);
	}
	// for(int i = 1; i < n; ++i) p = nxt(p);
	// while(p < k-1) p = nxt(p);
	cout.precision(30);
	cout << p << endl;
	// cout << p << endl;
}
