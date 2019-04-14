#include <bits/stdc++.h>
using namespace std;

int main() {
	int A, a, B, b, P;
	cin >> A >> a >> B >> b >> P;
	bool can = A + B <= P ||  A <= b || B <= a;
	if(can) cout << "Yes" << endl;
	else cout << "No" << endl;
}
