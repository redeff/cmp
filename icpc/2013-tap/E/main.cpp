#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t --> 0) {
		string s;
		cin >> s;
		int n = int(s.size());
		int p = 2;

		for(int l = 1; l <= n; ++l) {
			unordered_set<string> ns;
			for(int i = 0; i <= n - l; ++i) {
				string sub;
				for(int j = 0; j < l; ++j) {
					sub.push_back(s[i + j]);
				}
				ns.insert(sub);
			}
			if(int(ns.size()) < p) {
				cout << l << "\n";
				goto cont;
			} else {
				// cerr << "ALALA" << endl;
			}

			p *= 2;
		}

cont:;
	}
}
