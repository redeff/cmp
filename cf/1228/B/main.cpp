#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

typedef long long int ll;
ll mod = 1e9+7;

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> ns(n);
	for(int &i : ns) cin >> i;
	vector<int> ms(m);
	for(int &i : ms) cin >> i;
	
	vector<vector<int>> board(n, vector<int>(m, 0));
	
	forn(i, n) {
		forn(j, ns[i]) {
			board[i][j] |= 1;
		}
		if(ns[i] < m) board[i][ns[i]] |= 2;
	}

	forn(i, m) {
		forn(j, ms[i]) {
			board[j][i] |= 1;
		}
		if(ms[i] < n) board[ms[i]][i] |= 2;
	}

	ll total = 1;

	forn(i, n) forn(j, m) {
		if(board[i][j] == 0) {
			total *= 2;
			total %= mod;
		} else if(board[i][j] == 3) {
			total = 0;
		}
	}

	cout << total << endl;
}
