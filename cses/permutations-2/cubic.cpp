#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin >> n;
	vector<int> ns(n, 0);

	for(int x = 0; x < n; ++x) {
		for(int y = 0; y < n; ++y) cout << ns[x][y] << "\t";
		cout << endl;
	}
}
