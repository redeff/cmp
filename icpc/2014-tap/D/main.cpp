#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

typedef vector<vector<bool>> Grid;

typedef long long int ll;

pair<double, double> calc(Grid grid) {
	int n = int(grid.size());
	int m = int(grid.back().size());

	vector<ll> idp(1 << n, 0);
	vector<ll> dp(1 << n, 0);
	vector<ll> odp(1 << n, 0);
	dp[(1 << n)-1] = 1;
	for(int j = 0; j < m; ++j) {
		for(int i = 0; i < n; ++i) {
			vector<ll> ndp(1 << n, 0);
			vector<ll> ondp(1 << n, 0);
			vector<ll> indp(1 << n, 0);
			for(int b = 0; b < (1 << n); ++b) {
				int prv = i != 0 ? b & (1 << (i-1)) : -1;
				int ths = b & (1 << i);
				if(!grid[i][j]) {
					if(!ths) {
						ndp[b | (1 << i)] += dp[b];
						indp[b | (1 << i)] += idp[b] + dp[b];
						ondp[b | (1 << i)] += odp[b];
					}
					else {
						ndp[b & ~(1ull << i)] += dp[b];
						indp[b & ~(1ull << i)] += idp[b];
						ondp[b & ~(1ull << i)] += odp[b];
						if(i != 0 && !prv) {
							ndp[b | (1 << i) | (1 << (i-1))] += dp[b];
							indp[b | (1 << i) | (1 << (i-1))] += idp[b];
							ondp[b | (1 << i) | (1 << (i-1))] += odp[b] + dp[b];
							// assert(false);
						}
					}
				} else {
					// assert(false);
					if(ths) {
						ndp[b] += dp[b];
						indp[b] += idp[b];
						ondp[b] += odp[b];
					}
				}
			}
			swap(dp, ndp);
			swap(idp, indp);
			swap(odp, ondp);
		}
	}
	// cout << dp[3] << endl;
	double a = idp[(1 << n) - 1];
	double b = odp[(1 << n) - 1];
	return {a / (a+b), b / (a+b)};
}

const int N = 2;
void zero(double c[N][N]) {
	forn(i, N) forn(j, N) c[i][j] = 0;
}

void cp(double a[N][N], double c[N][N]) {
	forn(i, N) forn(j, N) a[i][j] = c[i][j];
}

void prod(double a[N][N], double b[N][N], double c[N][N]) {
	forn(i, N) forn(j, N) c[i][j] = 0;
	forn(i, N) forn(j, N) forn(k, N) c[i][j] += a[i][k] * b[k][j];
}

void ex(double a[N][N], double p[N][N], ll e) {
	zero(p);
	forn(i, N) p[i][i] = 1;
	while(e != 0) {
		double b[N][N];

		if(e % 2 == 1) {
			prod(a, p, b);
			cp(p, b);
		}

		prod(a, a, b);
		cp(a, b);

		e /= 2;
	}
}

int main() {
	// Grid grid(3, vector<bool>(3, false));
	// grid[1][1] = 1;
	// cout << calc(grid).first << " " << calc(grid).second << endl;
	//
	/*
	double m[N][N];
	m[0][0] = 1;
	m[0][1] = 1;
	m[1][0] = 1;
	m[1][1] = 0;

	double res[N][N];
	ex(m, res, 4);
	cout << res[0][0] << endl;
	*/
	int test;
	cin >> test;
	while(test --> 0) {
		int n, k;
		cin >> n >> k;
		Grid grid(n, vector<bool>(n));
		Grid dom(n, vector<bool>(2*n));
		Grid ver(n, vector<bool>(2*n));
		forn(i, n) forn(j, n) {
			int g;
			cin >> g;
			grid[i][j] = g == 1;

			dom[i][j] = g == 1;
			dom[i][n+j] = g == 1;

			ver[j][i] = g == 1;
			ver[j][n+i] = g == 1;
		}

		double m[N][N];
		auto p = calc(dom);
		m[0][0] = p.first;
		m[0][1] = p.second;
		p = calc(ver);
		m[1][0] = p.second;
		m[1][1] = p.first;
		// cerr << m[0][0] << " " << m[0][1] << " " << m[1][0] << " " << m[1][1] << endl;

		double res[N][N];
		// cerr << k << endl;
		ex(m, res, k);
		// cerr << res[0][0] << " " << res[0][1] << " " << res[1][0] << " " << res[1][1] << endl;

		p = calc(grid);
		// cerr << p.first << " " << p.second << endl;
		double r[N];
		r[0] = res[0][0] * p.first + res[1][0] * p.second;
		r[1] = res[0][1] * p.first + res[1][1] * p.second;
		// cerr << r[0] << " " << r[1] << endl;
		cout << setprecision(5);
		cout << fixed;
		cout << r[1] / (r[0] + r[1]) << endl;
	}
}
