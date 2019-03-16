#include <bits/stdc++.h>
using namespace std;

void print(int n) {
	if(n < 0) return;
	cout << "{";
	for(int i = 0; i < n; ++i) {
		if(i != 0) cout << ",";
		print(i);
	}
	cout << "}";
}

int main() {
	int n;
	cin >> n;
	n *= 2;
	vector<int> ns(n);
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		ns[i] = 0;
		for(char c : s) if(c == '{') ns[i]++;
		ns[i] = log2(ns[i]);
	}

	for(int i = 0; i < n/2; ++i) {
		print(ns[2*i] + ns[2*i+1]);
		cout << endl;
	}
}
