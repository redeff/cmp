#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;

	int mx = 1;
	int curr = 1;
	for(int i = 1; i < s.size(); ++i) {
		if(s[i] == s[i-1]) curr++;
		else curr = 1;

		mx = max(curr, mx);
	}

	cout << mx << endl;
}
