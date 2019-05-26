#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int BOUND = 6;
const ll mod = 1e9+7;

#define forxy for(int x = 0; x < BOUND; ++x) for(int y = 0; y < BOUND; ++y)

void multiply(ll a[BOUND][BOUND], ll b[BOUND][BOUND], ll c[BOUND][BOUND]) {
	forxy c[x][y] = 0;
	forxy for(int i = 0; i < BOUND; ++i) {
		c[x][y] += a[x][i] * b[i][y];
		c[x][y] %= mod;
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	unsigned long long int n;
	cin >> n;

	ll a[BOUND][BOUND];
	forxy a[x][y] = x + 1 == y || x == BOUND - 1;

	/*
	for(int x = 0; x < BOUND; ++x) {
		for(int y = 0; y < BOUND; ++y) {
			cout << a[x][y] << " ";
		}
		cout << endl;
	}
	*/

	ll b[BOUND][BOUND];
	forxy b[x][y] = x == y;

	ll c[BOUND][BOUND];

	ll (*m)[BOUND][BOUND] = &a;
	ll (*r)[BOUND][BOUND] = &b;
	ll (*l)[BOUND][BOUND] = &c;

	while(n) {
		if(n&1ull) {
			multiply(*m, *r, *l);
			swap(r, l);
		}
		multiply(*m, *m, *l);
		swap(m, l);

		n /= 2ull;
	}

	/*
	cout << endl;
	for(int x = 0; x < BOUND; ++x) {
		for(int y = 0; y < BOUND; ++y) {
			cout << (*r)[x][y] << " ";
		}
		cout << endl;
	}
	*/

	cout << (*r)[BOUND-1][BOUND-1] << "\n";
}
