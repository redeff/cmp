#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	int k;
	cin >> n >> k;
	cout << 3 * n + min(k - 1, n - k) << endl;
}
