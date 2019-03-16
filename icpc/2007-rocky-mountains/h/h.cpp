#include <bits/stdc++.h>
using namespace std;

pair<int, int> solve(int s, int r) {
	int a = (s + r) / 2;
	int b = s - a;
	return {a, b};
}

int main() {
	int n;
	while(cin >> n && n!= 0) {
		vector<int> ns(n);
		for(auto & x : ns) cin >> x;

		for(int p = 1; p < n; p *= 2) {
			vector<int> oth = ns;
			for(int i = 0; i < p; ++i) {
				auto pr = solve(ns[i], ns[i + p]);
				oth[2*i] = pr.first;
				oth[2*i+1] = pr.second;
			}
			ns = oth;
		}

		for(int i = 0; i < n; ++i) {
			cout << ns[i];
			if(i < n-1) cout << " ";
		}
		cout << endl;
	}
}
