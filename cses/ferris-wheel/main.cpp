#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x;
	cin >> n >> x;

	vector<int> ns(n);
	for(int &i : ns) cin >> i;

	sort(ns.begin(), ns.end());

	int a = 0;
	int b = n-1;
	int total = 0;
	while(a <= b) {
		if(ns[a] + ns[b] <= x) a++;
		b--;
		total++;
	}

	cout << total << endl;
}
