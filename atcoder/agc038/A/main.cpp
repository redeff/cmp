#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			bool res = j < a;
			if(i < b) res = !res;
			cout << res;
			// if(j != m-1) cout << " ";
		}
		cout << endl;
	}
}
