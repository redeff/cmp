#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> ns(n);
	for(int &i : ns) cin >> i;
	sort(ns.begin(), ns.end());

	vector<int> ms(m);
	for(int &i : ms) cin >> i;
	sort(ms.begin(), ms.end());

	int total = 0;
	while(!ns.empty() && !ms.empty()) {
		int a = ns.back();
		int b = ms.back();
		if(a > b + k) ns.pop_back();
		else if(b > a + k) ms.pop_back();
		else {
			ns.pop_back();
			ms.pop_back();
			total++;
		}
	}

	cout << total << endl;
}
