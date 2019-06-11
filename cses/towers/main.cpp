#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;

	multiset<int> curr;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;

		auto it = curr.upper_bound(a);
		if(it != curr.end()) curr.erase(it);
		curr.insert(a);
	}
	cout << curr.size() << endl;
}
