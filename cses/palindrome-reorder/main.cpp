// Palindrome Reorder CSES
#include <bits/stdc++.h>
using namespace std;

const int MAX = max('z', 'Z');

int main() {
	string s;
	cin >> s;

	vector<int> app(max('z', 'Z') + 1, 0);
	for(char c : s) app[c]++;
	int odd = 0;
	for(auto i : app) odd += i % 2;
	if(odd > 1) {
		cout << "NO SOLUTION" << endl;
	} else {
		string total;

		for(char c = 0; c <= MAX; ++c) {
			if(app[c] % 2 == 1) {
				for(int i = 0; i < app[c]; ++i) total.push_back(c);
			}
		}

		for(char c = 0; c <= MAX; ++c) {
			if(app[c] % 2 == 0) {
				for(int i = 0; i*2 < app[c]; ++i) total.push_back(c);
			}
		}

		reverse(total.begin(), total.end());

		for(char c = 0; c <= MAX; ++c) {
			if(app[c] % 2 == 0) {
				for(int i = 0; i*2 < app[c]; ++i) total.push_back(c);
			}
		}

		cout << total << endl;
	}
}
