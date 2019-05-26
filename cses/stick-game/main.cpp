#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int t;
	cin >> t;
	while(t --> 0) {
		int n;
		cin >> n;
		int total = 0;
		for(int i = 0; i < n; ++i) {
			int a;
			cin >> a;
			total ^= a % 4;
		}

		if(total == 0) cout << "second" << "\n";
		else cout << "first" << "\n";
	}
}
