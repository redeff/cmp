#include <bits/stdc++.h>
using namespace std;

int main() {
	int k;
	string s;
	while(cin >> k >> s && k != -1) {
		int n = s.size();
		string total = s;

		reverse(s.begin(), s.end());
		for(int i = 0; i <= k; ++i) {
			string out = s;
			int used = 0;
			for(int j = n - 1; j >= 0; --j) {
				if(out[j] != 'a' && used < i) {
					used++;
					out[j] = 'a';
				}
			}
			for(int j = i; j < k; ++j) out.push_back('a');

			reverse(out.begin(), out.end());
			total = min(total, out);
		}

		int not_a = 0;
		for(char c : s) if(c != 'a') not_a++;
		if(not_a <= k) {
			string out;
			for(int i = 0; i < n - k; ++i) out.push_back('a');
			total = min(total, out);
		}

		cout << total << endl;
	}
}
