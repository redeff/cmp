#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for(; t; --t) {
		int n;
		cin >> n;
		// vector<unsigned long long int> ns(n);
		unsigned int total = 0;
		for(int i = 0; i < n/2; ++i) {
			unsigned int a, b;
			cin >> a >> b;
			total ^= b;
		}
		
		if(total == 0) cout << "second" << "\n";
		else cout << "first" << "\n";

		if(n % 2 == 1) cin >> total;
	}
}
