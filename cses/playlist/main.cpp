#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) cin >> i;

	set<int> curr;
	int a = 0;
	int b = 0;
	int best = 0;
	while(a < n) {
		while(b < n && !curr.count(ns[b])) {
			curr.insert(ns[b]);
			++b;
		}
		
		best = max(best, (int) curr.size());

		curr.erase(ns[a]);
		++a;
	}

	cout << best << endl;
}
