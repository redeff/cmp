#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	cin >> s;
	int n = (int) s.size();
	vector<pair<char, int>> ns(n);
	for(int i = 0; i < n; ++i) ns[i] = {s[i], i};
	auto ord = ns;
	sort(ord.begin(), ord.end());
	vector<int> nxt(n);
	for(int i = 0; i < n; ++i) {
		int j = lower_bound(ord.begin(), ord.end(), ns[i]) - ord.begin();
		nxt[j] = i;
	}
	for(int i = nxt[0]; i != 0; i = nxt[i]) {
		cout << ord[i].first;
	}
	cout << endl;
}
