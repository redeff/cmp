#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll rec(ll n) {
	if(n == 0) return 0;
	return n/5 + rec(n/5);
}

int main() {
	ll n;
	cin >> n;
	cout << rec(n) << endl;
}
