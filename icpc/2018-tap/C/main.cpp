#include <bits/stdc++.h>
using namespace std;

const int bound = 10000;

int main() {
	string s = "46";

	for(int i = 0; i < 2*bound; ++i) {
		int a = s[s.size()-1] - '0';
		int b = s[s.size()-2] - '0';
		s += to_string(a*b);
	}

	int mod = -1;
	for(int i = bound+1; i < 2*bound; ++i) {
		if(s[bound-1] == s[i-1] && s[bound] == s[i]) {
			mod = i - bound;
			break;
		}
	}
	assert(mod != -1);

	for(int i = 0; i < 4; ++i) {
		int a;
		cin >> a;
		--a;
		if(a < bound) cout << s[a];
		else {
			a -= bound;
			a %= mod;
			a += bound;
			cout << s[a];
		}
	}
	cout << endl;
}
