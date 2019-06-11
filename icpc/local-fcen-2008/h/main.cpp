#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while(cin >> n && n != -1) {
		int s = 4*n-1;
		vector<string> ns(s, string(s, ' '));
		for(int i = 0; i < s; ++i) for(int j = 0; j < s; ++j) {
			ns[i][j] = "/\\ _\\/_ "[(j+2)%4*2+(i+1-n%2)%2];
		}
		for(int i = 0; i < s; ++i) {
			for(int j = 0; j < s; ++j) {
				if(2*i + j < 2*n-3+i%2) ns[i][j] = ' ';
			}
			reverse(ns[i].begin(), ns[i].end());
			for(int j = 0; j < s; ++j) {
				if(2*i + j < 2*n-3+i%2) ns[i][j] = ' ';
			}
			reverse(ns[i].begin(), ns[i].end());
		}

		reverse(ns.begin(), ns.end());

		for(int i = 0; i < s; ++i) {
			for(int j = 0; j < s; ++j) {
				if(2*i + j < 2*n-1) ns[i][j] = ' ';
			}
			reverse(ns[i].begin(), ns[i].end());
			for(int j = 0; j < s; ++j) {
				if(2*i + j < 2*n-1) ns[i][j] = ' ';
			}
			reverse(ns[i].begin(), ns[i].end());
		}

		for(string sa : ns) cout << sa << endl;
		cout << "***" << endl;
	}
}
