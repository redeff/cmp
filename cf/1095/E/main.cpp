#include <bits/stdc++.h>
using namespace std;

int val(char c) {
	if(c == '(') return 1;
	else return -1;
}

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;

	vector<int> depth(n+1, 0);
	for(int i = 0; i < n; ++i) depth[i+1] = depth[i] + val(s[i]);

	if(depth.back() != 2 && depth.back() != -2) {
		cout << 0 << endl;
		return 0;
	}

	if(depth.back() == 2) {
		reverse(s.begin(), s.end());
		for(char &c : s) c = 'Q' - c;
		depth[0] = 0;
		for(int i = 0; i < n; ++i) depth[i+1] = depth[i] + val(s[i]);
	}

	if(*min_element(depth.begin(), depth.end()) < -2) {
		cout << 0 << endl;
		return 0;
	}

	int total = 0;
	for(int i = 0; i < n; ++i) {
		if(depth[i] < 0) break;
		if(val(s[i]) < 0) total++;
	}

	cout << total << endl;
}
