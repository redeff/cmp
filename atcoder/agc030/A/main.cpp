#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	c = min(c, a + b + 1);
	cout << b + c << endl;
}
