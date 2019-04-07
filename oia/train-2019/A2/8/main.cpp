#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin >> n;
	vector<string> ns(n);
	for(int i = 0; i < n; ++i) {
		cin >> ns[i];
	}

	for(int i = n - 1; i > 0; --i) {
		int k = 0;
		while(k < ns[i].size() && k < ns[i-1].size() && ns[i][k] == ns[i-1][k]) k++;
		if(k == ns[i].size() || k == ns[i-1].size() || ns[i][k] < ns[i-1][k])
			while(ns[i-1].size() > k) ns[i-1].pop_back();
	}

	for(string s : ns) cout << s << endl;
}
