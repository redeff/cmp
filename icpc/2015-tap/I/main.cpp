#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for(int i = 0; i < n; ++i)

int sigma = 'z' - 'a' + 10;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	while(cin >> n) {
		string a, b;
		cin >> a >> b;
		vector<int> as(n);
		vector<int> bs(n);
		forn(i, n) as[i] = a[i]-'a';
		forn(i, n) bs[i] = b[i]-'a';

		int best = 0;
		forn(i, n) {
			vector<int> per(sigma, -1);
			vector<int> per_t(sigma, 0);
			vector<int> inv(sigma, -1);
			vector<int> inv_t(sigma, 0);

			int len = 0;
			int bck = -1;
			forn(j, 2*n) {
				int oth = (i + j) % n;
				int c = as[j%n];
				int d = bs[oth];
				if(per[c] == -1 && inv[d] == -1) {
					per[c] = d;
					per_t[c] = j;
					inv[d] = c;
					inv_t[d] = j;
					/*
					forn(x, sigma) {
						if(per[x] != -1) assert(inv[per[x]] == x);
						if(inv[x] != -1) assert(per[inv[x]] == x);
					}
					*/
				} else if (per[c] == d && inv[d] == c) {
					per_t[c] = j;
					inv_t[d] = j;
				} else {
					if(per[c] != -1) bck = max(bck, inv_t[per[c]]);
					bck = max(bck, per_t[c]);
					if(inv[d] != -1) bck = max(bck, per_t[inv[d]]);
					bck = max(bck, inv_t[d]);

					if(per[c] != -1) inv[per[c]] = -1;
					per[c] = -1;
					if(inv[d] != -1) per[inv[d]] = -1;
					inv[d] = -1;

					per[c] = d;
					per_t[c] = j;
					inv[d] = c;
					inv_t[d] = j;
				}
				len = max(len, j-bck);
			}
			best=max(best, len);
		}
		cout << min(best, n) << "\n";
	}
}
