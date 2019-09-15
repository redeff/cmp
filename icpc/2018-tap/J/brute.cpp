#include <bits/stdc++.h>
using namespace std;

bool game(string s, string t) {
	int n = int(s.size());
	int m = int(t.size());

	vector<vector<bool>> grundy(n+1, vector<bool>(m+1, false));
	for(int i = n; i >= 0; --i) for(int j = m-1; j >= 0; --j) {
		for(int k = i+1; k <= n; ++k) if(s[k-1] == t[j]) {
			grundy[i][j] = grundy[i][j] | !grundy[k][j+1];
		}
	}
	return grundy[0][0];
}

bool nxt(string &s) {
	int i = 0;
	while(i < s.size() && s[i] == 'c') {
		s[i] = 'a';
		++i;
	}
	if(i < s.size()) s[i]++;
	return i < s.size();
}

int main() {
	// int n;
	// cin >> n;
	string s;
	cin >> s;

	int total = 0;
	for(int i = 1; i <= s.size(); ++i) {
		string t(i, 'a');
		do {
			if(game(s, t)) {
				total++;
				cout << t << endl;
			}
		} while(nxt(t));
	}
	cout << total << endl;
}
