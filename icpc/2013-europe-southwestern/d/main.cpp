#include <bits/stdc++.h>
using namespace std;

bool alter(string s) {
	for(int i = 1; i < s.size(); ++i) {
		if(s[i-1] == s[i]) return false;
	}
	return true;
}

bool isin(int n, string s, bool odd) {
	if(s.size() == 0) return n >= 0;
	if(s.size() == 1) {
		// cerr << s << endl;
		if(s == "L" && odd) return n >= 1;
		else if(s == "L") return n >= 2;
		else if(s == "R" && odd) return n >= 2;
		else return n >= 3;
	}
	string a;
	string b;
	for(int i = 0; i < s.size(); ++i) {
		if(i % 2 == 0) a.push_back(s[i]);
		else b.push_back(s[i]);
	}

	if(odd) swap(a, b);
	
	bool rec_odd = (b[0] == 'L') == odd;
	if(!alter(b)) return false;
	bool res = isin(n-1, a, rec_odd);
	// cerr << n << " " << s << " " << odd << " " << res << endl;
	return res;
}

int main() {
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		bool works = isin(n, s, true) || isin(n, s, false);
		cout << "Case " << i+1 << ": " << (works ? "Yes" : "No") << endl;
	}
}
