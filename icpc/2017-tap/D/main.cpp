#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long double ld;
ld inf = numeric_limits<ld>::infinity();
ld eps = 1e-11;

const int bound = 200;
ld weis[bound][bound];
ld chan[bound];
ld best[bound];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;

	forn(i, n) cin >> chan[i];

	forn(i, n) forn(j, n) weis[i][j] = inf;
	forn(aklsjd, m) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		cin >> weis[a][b];
		weis[b][a] = weis[a][b];
	}

	ld lo = -1;
	ld hi = 1e6+1;

	while(hi - lo > eps) {
		ld mid = (hi + lo) / 2;
		// vector<ld> best(n, -inf);
		forn(i, n) best[i] = -1;
		best[0] = mid;

		bool ex;
		forn(laksjfskdjf, n+1) {
			ex = false;
			forn(i, n) forn(j, n) if(best[i] >= weis[i][j]) {
				ld nw = best[i] - weis[i][j];
				if(chan[j] <= chan[i]) nw *= chan[i] / chan[j];

				if(nw > best[j] + eps) {
					best[j] = nw;
					ex = true;
				}
			}
		}

		if(ex) hi = mid;
		else lo = mid;
	}

	int res = ceil(hi) + 0.5;

	if(res > 1e6) cout << -1 << "\n";
	else cout << res << "\n";
}
