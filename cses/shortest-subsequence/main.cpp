#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	int n = s.size();
	s.push_back('A');
	s.push_back('C');
	s.push_back('G');
	s.push_back('T');
	vector<int> from(n+4, -1);
	pair<int, int> dp[4] = {{1, n}, {1, n+1}, {1, n+2}, {1, n+3}};
	for(int i = 0; i < n; ++i) {
		int c;
		if(s[i] == 'A') c = 0;
		else if(s[i] == 'C') c = 1;
		else if(s[i] == 'G') c = 2;
		else if(s[i] == 'T') c = 3;
		else return -1;

		auto it = min_element(dp, dp+4);
		from[i] = it->second;
		dp[c].first = it->first+1;
		dp[c].second = i;
	}

	string res;
	int i = min_element(dp, dp+4)->second;
	while(i != -1) {
		res.push_back(s[i]);
		i = from[i];
	}

	reverse(res.begin(), res.end());

	cout << res << endl;
}
