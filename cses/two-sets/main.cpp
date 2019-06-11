#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if(n % 4 == 1 || n % 4 == 2) {
		cout << "NO" << endl;
		return 0;
	}

	int g = (n - n%4)/2;

	cout << "YES" << endl;
	cout << n-n/2 << endl;
	for(int i = 0; i < g/2; ++i) {
		cout << (n-2*i) << " ";
	}
	for(int i = g/2; i < g; ++i) {
		cout << (n-2*i-1) << " ";
	}
	if(n % 4 == 3) cout << "1 2 ";
	cout << endl;

	cout << n/2 << endl;
	for(int i = 0; i < g/2; ++i) {
		cout << (n-2*i-1) << " ";
	}
	for(int i = g/2; i < g; ++i) {
		cout << (n-2*i) << " ";
	}
	if(n % 4 == 3) cout << "3 ";
	cout << endl;
}
