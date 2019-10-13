#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef long double ld;
ld eps = 0.0001;
typedef long long int ll;

const int sigma = 'z'-'a'+1;

// ll dp[sigma*sigma][sigma*sigma][2];
// ll dp[sigma*sigma][2];
const int n = sigma*sigma;
const int m = 3*n+1;
ll dp[m][n];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int k;
	while(cin >> k && k != 0) {
		// forn(b, 2) forn(i, sigma*sigma) forn(j, sigma*sigma) dp[i][j][b] = 0;
		forn(j, m) forn(i, n) dp[j][i] = 0;

		struct Str {
			int from;
			int to;
			ll wei;
		};
		vector<Str> words(k);

		ld hi = 0;
		forn(i, k) {
			string s;
			cin >> s;
			int l = int(s.size());
			if(l < 2) {
				words[i].from = 0;
				words[i].to = 0;
				words[i].wei = 0;
			} else {
				words[i].from = (s[0]-'a') + sigma * (s[1]-'a');
				words[i].to = (s[l-2]-'a') + sigma * (s[l-1]-'a');
				words[i].wei = l;
			}
			hi = max(hi, ld(l));
		}

		forn(t, m-1) {
			for(auto w : words) {
				dp[t+1][w.to] = max(dp[t+1][w.to], dp[t][w.from] + w.wei);
			}
		}

		/*
		forn(i, n) {
			if(dp[m-1][i] != 0) {
				cerr << dp[m-1][i] << endl;
				goto bien;
			}
		}
		cout << "No solution.\n";
		continue;
bien:;
*/

		ld lo = 0;
		while(hi - lo > eps) {
			ld mid = (hi+lo)/2.0;
			forn(i, n) {
				ld best = 0.0;
				ld half;
				forn(j, m) {
					best = max(best, ld(dp[j][i]) - ld(j)*mid);
					if(j == n+3) half = best;
				}

				if(best > half + eps) {
					lo = mid;
					goto outside;
				}
			}
			hi = mid;
outside:;
		}
		if(lo < eps) cout << "No solution.\n";
		else cout << setprecision(2) << fixed << lo << "\n";
	}
}
