#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	ll n, k, m;
	cin >> n >> k >> m;
	string s;
	cin >> s;
	deque<char> d;
	for(char c : s) d.push_back(c - 'A');
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j <= k; ++j) {
			d.push_back(d.front());
			d.pop_front();
		}
		d.push_front((d.back() + 1) % ('Z' - 'A' + 1));
	}
	cerr << char(d.front() + 'A') << endl;
}
