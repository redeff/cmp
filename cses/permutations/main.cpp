#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if(n == 2 || n == 3) cout << "NO SOLUTION";
	else if(n == 1) cout << "1";
	else {
		int a = 1;
		int b = n;
		while(true) {
			if(b - a == 3) break;
			cout << (a++) << " ";
			if(b - a == 3) break;
			cout << (b--) << " ";
		}
		cout << a+2 << " ";
		cout << a+0 << " ";
		cout << a+3 << " ";
		cout << a+1;
	}
	cout << "\n";
}
