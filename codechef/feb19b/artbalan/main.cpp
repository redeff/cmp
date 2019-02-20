#include <bits/stdc++.h>
using namespace std;

int main() {
	int test;
	cin >> test;
	for(int testcase = 0; testcase < test; ++testcase) {
		string s;
		cin >> s;
		int n = s.size();
		vector<int> ch('Z' - 'A' + 1, 0);
		for(char c : s) ch[c - 'A']++;
		sort(ch.begin(), ch.end());
		reverse(ch.begin(), ch.end());
		int mn = 33333333;
		for(int i = 1; i <= 'Z' - 'A' + 1; ++i) {
			if(n % i == 0) {
				int total = 0;
				int target = n / i;
				for(int j = 0; j <= 'Z' - 'A'; ++j) {
					total += abs(ch[j] - ((j < i) ? target : 0));
				}
				total /= 2;
				mn = min(mn, total);
			}
		}
		cout << mn << endl;
	}
}
