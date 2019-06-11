#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t --> 0) {
		ll x, y;
		cin >> x >> y;
		ll m = max(x, y);
		ll c = m*m - m + 1;
		ll d = m%2*2-1;
		cout << c - d * x + d * y << " ";
	}
	cout << "\n";
}
