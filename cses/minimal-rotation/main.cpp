#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	cin >> s;
	int n = s.size();
	for(int i = 0; i < n; ++i) s.push_back(s[i]);
	// char c = min_element
	vector<int> cand(n);
	for(int i = 0; i < n; ++i) cand[i] = i;
	for(int size = 0; size < n; ++size) {
		{
			vector<int> ncand;
			ncand.push_back(cand[0]);
			for(int i = 1; i < cand.size(); ++i) if(cand[i] - cand[i-1] > size) ncand.push_back(cand[i]);
			swap(cand, ncand);
		}
		{
			char mn = 'z';
			for(int i : cand) mn = min(mn, s[i + size]);
			vector<int> ncand;
			for(int i : cand) if(s[i + size] == mn) ncand.push_back(i);
			swap(cand, ncand);
		}
	}
	for(int i = 0; i < n; ++i) cout << s[i + cand[0]];
	cout << "\n";
}
