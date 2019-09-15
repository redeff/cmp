#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(3842743);
	int n = 10;
	string s;
	for(int i = 0; i < n; ++i) s.push_back(rand() % 26 + 'a');

	cout << "1" << endl;
	cout << s;

	int m = 10;
	cout << " " << m << endl;
	for(int i = 0; i < m; ++i) {
		vector<int> rnd;
		for(int j = 0; j < 4; ++j) rnd.push_back(rand() % (n-1) + 1);
		sort(rnd.begin(), rnd.end());
		rnd[2]++;
		rnd[3]++;
		cout << rnd[0] << " " << rnd[1] << " " << rnd[2] << " " << rnd[3] << endl;
	}
}
