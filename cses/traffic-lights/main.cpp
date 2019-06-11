#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, n;
	cin >> x >> n;

	set<int> ns;
	ns.insert(0);
	ns.insert(x);

	multiset<int> lens;
	lens.insert(x);

	for(int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		ns.insert(p);
		auto it = ns.find(p);
		lens.erase(lens.find(*next(it) - *prev(it)));
		lens.insert(*next(it) - *it);
		lens.insert(*it - *prev(it));
		cout << *lens.rbegin() << endl;
	}
}
