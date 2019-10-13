#include <bits/stdc++.h>
using namespace std;

vector<int> dig(int n) {
	vector<int> res;
	while(n != 0) {
		res.push_back(n%10);
		n /= 10;
	}
	return res;
}

bool dist(int n) {
	auto ds = dig(n);
	for(int i = 0; i < int(ds.size()); ++i) {
		for(int j = 0; j < i; ++j) {
			if(ds[i] == ds[j]) return false;
		}
	}
	return true;
}

int main() {
	int l, r;
	cin >> l >> r;
	for(int i = l; i <= r; ++i) {
		if(dist(i)) {
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}
