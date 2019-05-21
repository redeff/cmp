#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;

	// vector<vector<int>> res(n, vector<int>(m, 0));
	// vector<vector<bool>> ns(n, vector<bool>(m, false));
	int res[1000][1000];
	// bitset<1000> ns[1000];
	bool ns[1000][1000];

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < m; ++j) {
			ns[i][j] = s[j] == '*';
			res[i][j] = 0;
		}
	}

	for(int i = 0; i < n; ++i) {
		for(int x = 0; x < n-i; ++x) {
			int last = 0;
			for(int y = 0; y < m; ++y) {
				if(ns[x][y]) last = y+1;
				else {
					res[i][y - last]++;
				}
			}
		}
		for(int x = 0; x < n-1; ++x) {
			// ns[x] = ns[x] | ns[x+1];
			for(int y = 0; y < m; ++y) {
				ns[x][y] = ns[x][y] | ns[x+1][y];
			}
		}
	}

	/*
	for(int x = n-2; x >= 0; --x) for(int y = 0; y < m; ++y) {
		res[x][y] += res[x+1][y];
	}

	*/
	for(int x = 0; x < n; ++x) for(int y = m-2; y >= 0; --y) {
		res[x][y] += res[x][y+1];
	}

	for(int x = 0; x < n; ++x) {
		for(int y = 0; y < m; ++y) cout << res[x][y] << " ";
		cout << "\n";
	}
}
