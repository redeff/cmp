#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

// Yo no hago plagio
// LALALALA
// jsdjkfljdflakjsf
// skjadlfkjlaskjf
// slkdjflaksjdflkasjdflaksjdf
// lkkjdflksjdlfjaoijfsvnksjnvkajoasneiinr
// i ucrnwnoceoe

bool mat[75][75];
bool prv[75];
bool now[75];
void caso(int n, vector<int> &res) {
	string s;
	forn(i, n) {
		cin >> s;
		forn(j, n) mat[i][j] = s[j] == '1';
	}

	forn(i, n) {
		forn(o, n) now[o] = prv[o] = false;
		prv[i] = true;
		forn(o, n) now[o] = prv[o];
		forn(o, n) forn(p, n) now[p] |= mat[o][p] && prv[o];
		bool works = true;
		forn(o, n) if(!now[o]) works = false;
		if(works) {
			// cout << 1 << endl;
			// return 0;
			res = {i};
			return;
		}
	}

	forn(i, n) {
		forn(j, i) {
			forn(o, n) now[o] = prv[o] = false;
			prv[i] = true;
			prv[j] = true;
			forn(o, n) now[o] = prv[o];
			forn(o, n) forn(p, n) now[p] |= mat[o][p] && prv[o];
			bool works = true;
			forn(o, n) if(!now[o]) works = false;
			if(works) {
				res = {i, j};
				return;
			}
		}
	}

	forn(i, n) {
		forn(j, i) {
			forn(k, j) {
				forn(o, n) now[o] = prv[o] = false;
				prv[i] = true;
				prv[j] = true;
				prv[k] = true;
				bool works = true;
				forn(p, n) {
					now[p] = prv[p]
						|| mat[i][p] && prv[i]
						|| mat[j][p] && prv[j]
						|| mat[k][p] && prv[k];
					if(!now[p]) {
						works = false;
						break;
					}
				}
				if(works) {
					res = {i, j, k};
					return;
				}
			}
		}
	}

	forn(i, n) {
		forn(j, i) {
			forn(k, j) {
				forn(l, k) {
					forn(o, n) now[o] = prv[o] = false;
					prv[i] = true;
					prv[j] = true;
					prv[k] = true;
					prv[l] = true;
					bool works = true;
					forn(p, n) {
						now[p] = prv[p]
							|| mat[i][p] && prv[i]
							|| mat[j][p] && prv[j]
							|| mat[k][p] && prv[k]
							|| mat[l][p] && prv[l];
						if(!now[p]) {
							works = false;
							break;
						}
					}
					if(works) {
						res = {i, j, k, l};
						return;
					}
				}
			}
		}
	}

	forn(i, n) {
		forn(j, i) {
			forn(k, j) {
				forn(l, k) {
					forn(m, l) {
						forn(o, n) now[o] = prv[o] = false;
						prv[i] = true;
						prv[j] = true;
						prv[k] = true;
						prv[l] = true;
						prv[m] = true;
						bool works = true;
						forn(p, n) {
							now[p] = prv[p]
								|| mat[i][p] && prv[i]
								|| mat[j][p] && prv[j]
								|| mat[k][p] && prv[k]
								|| mat[l][p] && prv[l]
								|| mat[m][p] && prv[m];
							if(!now[p]) {
								works = false;
								break;
							}
						}
						if(works) {
							res = {i, j, k, l, m};
							return;
						}
					}
				}
			}
		}
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	int test = 0;
	vector<int> v;
	while(cin >> n) {
		++test;
		caso(n, v);
		cout << "Case " << test << ": ";
		cout << v.size();
		for(int i : v) cout << " " << i+1;
		cout << "\n";
	}
}
