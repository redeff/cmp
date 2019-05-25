#include <bits/stdc++.h>
using namespace std;

void po(vector<int> &base, vector<int> &to, vector<int> &buff, int n, int e, int stride, int wei) {
	if(e == 0) {
		for(int i = 0; i < n; ++i) to[i] = base[i];
	} else {
		po(base, buff, to, n, e/2, stride, wei);
		for(int i = 0; i < n; ++i) {
			to[i] = buff[i];
			if(i - stride * (e/2) >= 0) {
				to[i] = max(to[i], buff[i - stride * (e/2)] + (e/2) * wei);
			}
			if(i - stride * e >= 0 && e % 2 == 1) {
				to[i] = max(to[i], base[i - stride * e] + e * wei);
			}
		}
	}
}

// const int BOUND = 1e5;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, x;
	cin >> n >> x;
	++x;
	// ++x;
	vector<int> hs(n);
	for(int &i : hs) cin >> i;
	vector<int> ss(n);
	for(int &i : ss) cin >> i;
	vector<int> ks(n);
	for(int &i : ks) cin >> i;

	vector<int> base(x, 0);
	vector<int> to(x);
	vector<int> buff(x);
	for(int i = 0; i < n; ++i) {
		po(base, to, buff, x, ks[i], hs[i], ss[i]);
		base = to;
	}

	// for(int i : to) cout << i << " ";
	// cout << endl;
	cout << *max_element(base.begin(), base.end()) << "\n";
}
