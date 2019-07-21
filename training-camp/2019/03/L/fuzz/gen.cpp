#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 7;
	int m = 20;
	cout << n << " " << m << endl;

	srand(14579278);
	vector<pair<int, int>> edges;
	for(int i = 0; i < m; ++i) {
		int a = rand() % n + 1;
		int b = rand() % (n-1) + 1;
		if(b == a) ++b;

		cout << a << " " << b << endl;
		edges.push_back({a, b});
	}

	int q = 1000;
	cout << q << endl;
	for(int i = 0; i < q; ++i) {
		int t = rand() % 2 + 1;
		cout << t << " ";
		if(t == 1) {
			int a = rand() % n + 1;
			int b = rand() % (n-1) + 1;
			if(b == a) ++b;

			int index = rand() % m;
			cout << a << " " << b << " " << edges[index].first << " " << edges[index].second << endl;
		} else {
			int a = rand() % n + 1;
			int b = rand() % (n-1) + 1;
			if(b == a) ++b;
			int c = rand() % (n-2) + 1;
			if(a == c) ++c;
			if(b == c) ++c;
			if(a == c) ++c;

			cout << a << " " << b << " " << c << endl;
		}
	}
}
