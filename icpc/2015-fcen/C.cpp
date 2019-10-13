#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef long long int ll;

struct pto {
	ll x; ll y;
	pto(ll x_, ll y_): x(x_), y(y_) {}
	pto() {}
};

ll operator%(pto a, pto b) {
	return abs(a.x*b.y - a.y*b.x);
}

pto operator-(pto a, pto b) {
	return pto(a.x-b.x, a.y-b.y);
}

int main() {
	int n;
	while(cin >> n) {
		vector<pto> ns(n);
		forn(i, n) cin >> ns[i].x >> ns[i].y;
		ll area = 0;
		forn(i, n-1) {
			area += (ns[i+1] - ns[0]) % (ns[i] - ns[0]);
		}
		ll curr = 0;
		int j = 0;
		ll res = 5e16;
		forn(i, n) {
			ll k = 0;
			while(true) {
				k = max(k, min(curr, area-curr));
				int nxt = (j+1)%n;
				ll extra = (ns[nxt] - ns[i]) % (ns[j] - ns[i]);
				if(2*(curr + extra) <= area) {
					j = nxt;
					curr += extra;
				} else {
					k = max(k, curr);
					k = max(k, area - curr - extra);
					break;
				}
			}
			// cerr << k << " ";
			res = min(res, k);
			curr -= (ns[j] - ns[i]) % (ns[(i+1)%n] - ns[i]);
		}
		// cerr << endl;
		cout << area - res << " " << res << endl;
	}
}
