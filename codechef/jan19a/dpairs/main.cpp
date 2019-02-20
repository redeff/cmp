#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int a, b;
	cin >> a >> b;

	vector<ll> as(a);
	vector<int> ias(a);
	for(int i = 0; i < a; ++i) {
		cin >> as[i];
		ias[i] = i;
	}
	sort(ias.begin(), ias.end(), [&](int n, int m) { return as[n] < as[m]; });

	vector<ll> bs(b);
	vector<int> ibs(b);
	for(int i = 0; i < b; ++i) {
		cin >> bs[i];
		ibs[i] = i;
	}
	sort(ibs.begin(), ibs.end(), [&](int n, int m) { return bs[n] < bs[m]; });

	for(int i = 0; i < a; ++i) {
		cout << ias[i] << " " << ibs[0] << endl;
	}

	for(int i = 1; i < b; ++i) {
		cout << ias.back() << " " << ibs[i] << endl;
	}
}
