#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	int n = 500;
	int BOUND = 20000;
	cout << n << endl;
	cout << -1 << " ";
	for(int i = 1; i < n; ++i) cout << rand() % i << " ";
	cout << endl;
	for(int i = 0; i < n; ++i) cout << rand() % BOUND << " ";
	cout << endl;
	for(int i = 0; i < n; ++i) cout << rand() % BOUND << " ";
	cout << endl;

}
