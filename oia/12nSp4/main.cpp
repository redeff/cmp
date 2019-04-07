#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
#ifndef LOCAL
#define cout lasfalshdf
#define cin sjdhflashdflahsdl
	ifstream cin("toneles.in");
	ofstream cout("toneles.out");
#endif
	int l;
	int n;
	cin >> l >> n;

	vector<int> ns(n+1);
	for(int &i : ns) cin >> i;
	ns[n] = 0;

	vector<int> sums(n);
	sums[0] = ns[0];
	for(int i = 1; i < n; ++i) sums[i] = sums[i-1] + ns[i];

	ll total = 0;
	int gud = -1;

	for(int i = 0; i < n; ++i) {
		int curr = (sums[i] + l - 1) / l;
		total += (ll) curr;
		if(curr > (sums[i] - min(ns[i], l - ns[i+1]) + l - 1) / l) {
			gud = i;
		}
	}

	cout << total << endl;
	cout << gud + 1 << endl;
}
