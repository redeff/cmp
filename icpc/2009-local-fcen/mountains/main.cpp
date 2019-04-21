#include <bits/stdc++.h>
using namespace std;

int main() {
	int c;
	while(cin >> c && c!= -1) {
		vector<int> ns(c+1);
		for(int &i : ns) cin >> i;
		int mx = 0;
		for(int i = 0; i < c; ++i) mx = max(mx, min(ns[i], ns[i+1]));
		vector<vector<char>> block(mx+1, vector<char>(c, ' '));
		for(int i = 0; i < c; ++i) {
			int t = min(ns[i], ns[i+1]);
			char ch;
			if(ns[i] == ns[i+1]) {
				ch = '_';
			} else if(ns[i] < ns[i+1]) {
				ch = '/';
			} else {
				ch = '\\';
			}
			// cerr << mx - t + 3 << endl;
			block[mx - t][i] = ch;
		}
		for(vector<char> &s : block) while(!s.empty() && s.back() == ' ') s.pop_back();
		for(vector<char> s : block) {
			for(char a : s) cout << a;
			cout << endl;
		}
		cout << "***" << endl;
	}
}
