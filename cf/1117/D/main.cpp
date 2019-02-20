#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

#define M 105
const ll MOD = 1000000007;

void zero(ll a[M][M]) {
	for(int i = 0; i < M; ++i) for(int j = 0; j < M; ++j) a[i][j] = 0;
}

void mult(ll a[M][M], ll b[M][M], ll c[M][M]) {
	zero(c);
	for(int i = 0; i < M; ++i) for(int j = 0; j < M; ++j) for(int k = 0; k < M; ++k) {
		c[i][j] += a[i][k] * b[k][j];
		c[i][j] %= MOD;
	}
}

void id(ll a[M][M]) {
	for(int i = 0; i < M; ++i) for(int j = 0; j < M; ++j) a[i][j] = (i == j) ? 1 : 0;
}

void mv(ll a[M][M], ll b[M][M]) {
	for(int i = 0; i < M; ++i) for(int j = 0; j < M; ++j) b[i][j] = a[i][j];
}

void ex(ll a[M][M], ll b[M][M], ll c[M][M], ll v) {
	if(v == 0) return;
	if(v % 2 == 1) {
		mult(a, b, c);
		mv(c, b);
	}
	mult(a, a, c);
	mv(c, a);
	ex(a, b, c, v/2);
}

int main() {
	ll n, m;
	cin >> n >> m;

	ll a[M][M];
	ll b[M][M];
	ll c[M][M];

	zero(a);
	id(b);
	zero(c);

	for(int i = 0; i < M - 1; ++i) a[i + 1][i] = 1;
	a[0][0] = 1;
	a[0][m-1] = 1;

	ex(a, b, c, n);

	cout << b[0][0] << endl;
}
