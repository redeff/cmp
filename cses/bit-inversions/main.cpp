#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	string bits;
	cin >> bits;
	int n = (int) bits.size();

	set<int> bars;
	bars.insert(0);
	bars.insert(n);

	multiset<int> lens;
	lens.insert(n);

	function<void(int)> update = [&](int i) {
		auto it = bars.find(i);
		if(it == bars.end()) {
			bars.insert(i);
			it = bars.find(i);
			lens.insert(*it - *prev(it));
			lens.insert(*next(it) - *it);
			lens.erase(lens.find(*next(it) - *prev(it)));
		} else {
			lens.erase(lens.find(*it - *prev(it)));
			lens.erase(lens.find(*next(it) - *it));
			lens.insert(*next(it) - *prev(it));
			bars.erase(*it);
		}
	};

	for(int i = 1; i < n; ++i) {
		if(bits[i] != bits[i-1]) {
			update(i);
		}
	}

	int m;
	cin >> m;
	for(int i = 0; i < m; ++i) {
		/*
		for(int j : bars) cout << j << " ";
		cout << endl;
		*/
		int k;
		cin >> k;
		k--;
		if(k != 0) update(k);
		if(k != n-1) update(k+1);
		bits[k] = '0' + '1' - bits[k];
		// cout << bits << endl;

		cout << *lens.rbegin() << " ";
	}
	cout << "\n";
}
