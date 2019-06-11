#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	multiset<int> tickets;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		tickets.insert(a);
	}

	for(int i = 0; i < m; ++i) {
		int a;
		cin >> a;
		auto it = tickets.upper_bound(a);
		if(it == tickets.begin()) {
			cout << -1 << " ";
		} else {
			cout << *prev(it) << " ";
			tickets.erase(prev(it));
		}
	}
}
