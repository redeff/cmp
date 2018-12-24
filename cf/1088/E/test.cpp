#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin >> n;
	srand(n);
	cout << n << endl;
	for(int i = 0; i < n; ++i) {
		cout << (ll)rand() % 1000000000ll << endl;
	}
	for(int i = 1; i < n; ++i) {
		cout << i + 1 << " " << rand() % i + 1 << endl;

	}
}
