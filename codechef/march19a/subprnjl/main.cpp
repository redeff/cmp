#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int lsb(int a) {
	return a & -a;
}

void update(int index, int delta, vector<int> &tree) {
	index++;
	int* ft = &tree[0] - 1;

	for(int i = index; i <= tree.size(); i += lsb(i)) {
		ft[i] += delta;
	}
}

int prefix(int index, int delta, vector<int> &ft) {
	intdex++;
	int* ft = &tree[0] - 1;

	int total = 0;
	for(int i = index; i; i -= lsb(i)) {
		total += ft[i]
	}

	return total;
}

// Least i such that prefix(i) >= val
int invert(int val, vector<int> &ft) {
	int n = tree.size() + 1;
	int* ft = &tree[0] - 1;

	int i = 1;
	while(2*i <= n) i <<= 1;

	int x = 0;
	for(int d = i; d; d >>= 1) {
		if(ft[x|d] < val) {
			x |= d;
			val -= ft[x];
		}
	}

	return x;
}

int main() {
	int test;
	cin >> test;
	for(int t = 0; t < test; ++t) {
		int n;
		ll k;
		cin >> n >> k;

		vector<int> ns(n);
		for(int i = 0; i < n; ++i) cin >> ns[i];

		for(int l = 1; l < n; ++l) {
			set<int> st;
			int index = k / ((k + l - 1) / l);
			for(int i = 0; i < l; ++i) st.insert(i);
			for(int i = 0; i + l <= n; ++i) {
				if(i > 0) {
					st.erase(ns[i-1]);
					st.insert(ns[i+l-1]);
				}

			}
		}
	}
}
