#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	cin >> testcase;
	for(int t = 0; t < testcase; ++t) {
		int b, n, f;
		cin >> n >> b >> f;

		vector<vector<bool>> ns(f);
		for(int i = 0; i < f; ++i) {
			ns[i] = vector<bool>(n);
			for(int j = 0; j < n; ++j) ns[i][j] = (j / (1 << i)) % 2;
			for(bool b : ns[i]) cout << b;
			cout << endl << flush;
			string s;
			cin >> s;
			ns[i] = vector<bool>();
			for(char c : s) ns[i].push_back(c == '1');
		}

		int index = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < f; ++j) {
				if(ns[j][index] != bool((i / (1 << j)) % 2)) {
					cout << i << " ";
					goto outer;
				}
			}

			index++;
outer:;
		}
		cout << endl << flush;

		int s;
		cin >> s;
		if(s == -1) exit(0);
	}
}

