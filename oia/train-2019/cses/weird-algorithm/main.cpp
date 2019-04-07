#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	ll n;
	cin >> n;
	while(n != 1ll) {
		cout << n << endl;
		if(n % 2ll == 0ll) n /= 2ll;
		else n = 3ll*n + 1ll;
	}
	cout << 1 << endl;
}
