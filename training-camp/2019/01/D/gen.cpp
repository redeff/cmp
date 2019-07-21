#include <bits/stdc++.h>
using namespace std;

int N = 10000;
int M = 10000;

int T = 77;

int main() {
	cout << T << endl;
	srand(12345);
	for(int test = 0; test < 77; ++test) {
		cout << N << " " << M << endl;
		set<pair<int, int>> tot;
		for(int i = 0; i < M; ++i) {
			int a, b;
			do {
				a = rand() % N + 1;
				b = rand() % (N-1) + 1;
				if(b == a) ++b;
				if(a > b) swap(a, b);
			} while(tot.count(make_pair(a, b)));
			tot.insert(make_pair(a, b));
			cout << a << " " << b << "\n";
		}
	}
}
