#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int i = 0; i < n; ++i) cin >> ns[i];
	int m = *max_element(ns.begin(), ns.end());
	vector<int> run(n + 1, 0);
	for(int i = 0; i < n; ++i) if(ns[i] == m) run[i + 1] = run[i] + 1;
	cout << *max_element(run.begin(), run.end()) << endl;
}
