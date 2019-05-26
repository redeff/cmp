#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+1;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> ns(N, 0);
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		ns[a]++;
	}

	int best = 0;
	for(int g = 1; g < N; ++g) {
		int total = 0;
		for(int i = 0; i < N; i += g) total += ns[i];
		if(total > 1) best = g;
	}
	cout << best << "\n";
}
