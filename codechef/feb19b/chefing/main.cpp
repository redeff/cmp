#include <bits/stdc++.h>
using namespace std;

int main() {
	int test;
	cin >> test;
	for(;test;test--) {
		int n;
		cin >> n;
		vector<bool> sp('z' - 'a' + 1, true);
		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			for(char c = 'a'; c <= 'z'; ++c) {
				if(find(s.begin(), s.end(), c) == s.end()) sp[c - 'a'] = false;
			}
		}

		int total = 0;
		for(bool b : sp) if(b) total++;
		cout << total << endl;
	}
}
