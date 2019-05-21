#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) cin >> i;

	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		vector<int> all;
		for(int j = a; j < b; ++j) all.push_back(ns[j]);
		sort(all.begin(), all.end());
		all.erase(unique(all.begin(), all.end()), all.end());
		cout << all.size() << endl;
	}
}
