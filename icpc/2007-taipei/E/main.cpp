#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

int inf = 33333333;

const int BOUND = 512;
int mat[BOUND][BOUND];
int bip[BOUND][BOUND];
int flo[BOUND][BOUND];
int opt[BOUND][BOUND];
int match[BOUND];

int main() {
	int test;
	cin >> test;
	while(test --> 0) {
		int n, m;
		cin >> n >> m;
		forn(i, n) forn(j, n) mat[i][j] = i == j ? 0 : inf;

		forn(alksjda, m) {
			int a, b, t;
			cin >> a >> b >> t;
			--a; --b;
			mat[a][b] = min(mat[a][b], t);
			mat[b][a] = min(mat[b][a], t);
		}

		forn(k, n) forn(i, n) forn(j, n)
			mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);


		int r;
		cin >> r;
		vector<int> rs(r);
		vector<int> fs(r);
		forn(i, r) {
			cin >> rs[i] >> fs[i];
			rs[i]--;
			fs[i]--;
		}

		int c;
		cin >> c;
		vector<int> cs(c);
		forn(i, c) {
			cin >> cs[i];
			cs[i]--;
		}

		int p;
		cin >> p;
		vector<int> ps(p);
		forn(i, p) {
			cin >> ps[i];
			ps[i]--;
		}

		forn(i, r) forn(j, r) {
			if(j < c) {
				bip[i][j] = inf;
				forn(k, p) {
					bip[i][j] = min(bip[i][j], 0
						+ mat[rs[i]][cs[j]]
						+ mat[cs[j]][ps[k]]
						+ mat[ps[k]][fs[i]]
						);
				}
			} else {
				bip[i][j] = mat[rs[i]][fs[i]];
				// cerr << rs[i] << " " << fs[i] << endl;
				assert(bip[i][j] > 0);
			}
		}

		int total = 0;
		forn(i, r) {
			match[i] = i;
			total += bip[i][i];
		}

		/*
		forn(i, r) {
			forn(j, r) cerr << bip[i][j] << " ";
			cerr << endl;
		}
		*/

again:;
		forn(i, r) forn(j, r) {
			flo[i][j] = bip[i][match[j]] - bip[i][match[i]];
			opt[i][j] = j;
		}
		forn(k, r) forn(i, r) forn(j, r) {
			if(flo[i][j] > flo[i][k] + flo[k][j]) {
				flo[i][j] = flo[i][k] + flo[k][j];
				opt[i][j] = opt[i][k];
				total += flo[i][j];
				if(i == j) {
					int init = match[i];
					do {
						if(opt[i][j] != j)
							match[i] = match[opt[i][j]];
						else match[i] = init;
						i = opt[i][j];
					} while(i != j);
					goto again;
				}
			}
		}

		int tot = 0;
		forn(i, r) tot += bip[i][match[i]];
		// assert(tot == total);
		total = tot;

		int minu = (total+r-1)/r;
		cout << setfill('0') << setw(2);
		cout << 8 + minu/60 << ":";
		cout << setfill('0') << setw(2);
		cout << minu%60 << endl;
	}
}
