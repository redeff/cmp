#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

int main() {
	int test;
	cin >> test;
	while(test --> 0) {
		int n;
		cin >> n;
		vector<int> ns(n);
		forn(i, n) {
			cin >> ns[i];
			ns[i] = -ns[i];
		}

		vector<int> curr;
		forn(i, n) {
			auto it = lower_bound(curr.begin(), curr.end(), ns[i]);
			if(it == curr.end()) curr.push_back(ns[i]);
			else *it = ns[i];
		}
		cout << curr.size() << endl;
	}
}
