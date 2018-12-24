#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll a, b;
	cin >> a >> b;
	while(true) {
		string s;
		int c, d;
		cin >> s >> c >> d;
		if(s == "?") {
			if((a^c) > (b^d)) cout << 1 << endl;	
			else if((a^c) < (b^d)) cout << -1 << endl;	
			else cout << 0 << endl;
		} else {
			cerr << c << " " << d << endl;
			assert(a == c && b == d);
		}
	}
}
