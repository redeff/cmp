#include <bits/stdc++.h>
using namespace std;

int main () {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) cin >> i;
	cout << accumulate(ns.begin(), ns.end(), 0) << endl;
}
