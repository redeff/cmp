#include <bits/stdc++.h>
using namespace std;

int main() {
	int l, n;
	while(cin >> l && l != -1) {
		cin >> n;

		vector<int> words(n);
		for(int i = 0; i < n; ++i) {
			string word;
			cin >> word;
			words[i] = word.size() + 1;
		}

		int mn = *max_element(words.begin(), words.end());
		int lo = mn - 1;
		int hi = accumulate(words.begin(), words.end(), 0);

		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			int lines = 1;
			int sum = 0;
			for(int i : words) {
				if(sum + i > mid) {
					lines++;
					sum = i;
				} else {
					sum += i;
				}
			}
			if(lines > l) lo = mid;
			else hi = mid;
		}

		cout << hi - 1 << endl;
	}
}
