#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int POW = 19;
const int BOUND = 1 << POW;
const int INDEX = 1 << (POW - 1);

ll st[BOUND];

void set_st(int node, ll val) {
	assert(node < INDEX);
	node ^= INDEX;
	st[node] = val;
	while(true) {
		node /= 2;
		if(node == 0) break;

		st[node] = max(st[2 * node], st[2 * node + 1]);
	}
}

int first_geq(ll val) {
	if(st[1] < val) {
		return -1;
	}
	assert(st[1] >= val);
	int node = 2;
	for(int i = 1; i < POW; ++i, node *= 2) {
		assert(st[node/2] >= val);
		if(st[node] < val) node++;
		assert(st[node] >= val);
	}
	node /= 2;
	// cerr << bitset<30>(node) << endl;
	// cerr << bitset<30>(INDEX) << endl;
	assert((node^INDEX) < INDEX);
	assert(st[node] >= val);
	return node ^ INDEX;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	for(int i = 0; i < BOUND; ++i) st[i] = 0;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		set_st(i, a);
	}

	for(int i = 0; i < m; ++i) {
		int a;
		cin >> a;
		int k = first_geq(a);
		if(k == -1) {
			cout << 0 << " ";
		} else {
			cout << k+1 << " ";
			st[k ^ INDEX] -= a;
			set_st(k, st[k ^ INDEX]);
		}
	}
	cout << endl;
}
