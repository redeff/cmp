#include <bits/stdc++.h>
using namespace std;

const int LET = 'z' - 'a' + 1;

int main() {
	string s;
	cin >> s;

	int n = s.size();

	string query(n, 'a');
	string s0, s1, s2;

	for(int i = 0; i < n; ++i) {
		query[i] = 'a' + i % LET;
	}
	cout << "? " << query << endl;
	cin >> s0;

	for(int i = 0; i < n; ++i) {
		query[i] = 'a' + (i / LET) % LET;
	}
	cout << "? " << query << endl;
	cin >> s1;

	for(int i = 0; i < n; ++i) {
		query[i] = 'a' + (i / LET / LET) % LET;
	}
	cout << "? " << query << endl;
	cin >> s2;

	string out(n, 'a');
	for(int i = 0; i < n; ++i) {
		int index = 0;
		index += s2[i] - 'a';
		index *= LET;
		index += s1[i] - 'a';
		index *= LET;
		index += s0[i] - 'a';
		out[index] = s[i];
	}

	cout << "! " << out << endl;
}
