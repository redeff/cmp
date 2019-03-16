#include <bits/stdc++.h>
using namespace std;

int main() {
	string a;
	string b;
	while(cin >> a >> b && a != "*") {
		
		vector<vector<int>> ns(a.size() + 1, vector<int>(b.size() + 1));
		for(int i = 0; i <= a.size(); ++i) ns[i][0] = i;
		for(int i = 0; i <= b.size(); ++i) ns[0][i] = i;

		for(int i = 1; i <= a.size(); ++i) for(int j = 1; j <= b.size(); ++j) {
			ns[i][j] = min(ns[i-1][j] + 1, ns[i][j-1] + 1, ns[i-1][j-1] + !(a[i-1] == b[j-1]));
			if(i >= 3 && j >= 3 &&  a[i-3] == b[j-2] && a[i-2] == b[i-3]) {
				ns[i][j] = min(ns[i][j], ns[i-2][j-2] + 1);
			}

			cout << ns.back().back() << endl;
		}
	}
}
