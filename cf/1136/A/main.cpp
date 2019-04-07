#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i] >> ns[i];
	int k;
	cin >> k;
	int total = 0;
	for(int x : ns) if(k > x) total++;
	cout << n - total << endl;
}
