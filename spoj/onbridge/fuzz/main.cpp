#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int n = 10;
	int m = 45;
	cout << 1 << endl;
	cout << n << " " << m << endl;
	unordered_set<ll> used;

	srand(109284834);

	for(int i = 0; i < m; ++i) {
		int t, a, b;
		do {
			a = rand() % n;
			b = rand() % (n-1);
			if(a == b) ++b;

			t = a + n * (ll)b;
		} while(used.count(t));
		used.insert(t);
		cout << a << " " << b << endl;
	}
}
