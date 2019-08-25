#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int test;
	cin >> test;
	while(test --> 0) {
		ll a, b;
		cin >> a >> b;
		bool can = (a + b) % 3 == 0 && a <= 2*b && b <= 2*a;
		cout << (can ? "YES" : "NO") << endl;
	}
}
