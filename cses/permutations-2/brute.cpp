#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

void brute_rec(int *ns, int n, int *left, int l, ll &total) {
	if(l == 0) total++;
	for(int i = 0; i < l; ++i) {
		int t = left[i];
		if(abs(t - ns[n-1]) != 1) {
			swap(left[i], left[l-1]);
			ns[n] = t;

			brute_rec(ns, n+1, left, l-1, total);

			swap(left[i], left[l-1]);
		}
	}
}

ll brute(int n) {
	vector<int> ns(n+1);
	ns[0] = -2;
	vector<int> left(n);
	for(int i = 0; i < n; ++i) left[i] = i;

	ll total = 0;
	brute_rec(&ns[0], 1, &left[0], n, total);

	return total;
}

int main() {
	for(int n = 4; n < 20; ++n) {
		cout << n << " " << brute(n) << endl;
	}
	int n;
	/*
	for(int n = 1; n < 14; ++n) {

		ll total = 0;
		ll fact = 0;

		vector<int> per(n);
		for(int i = 0; i < n; ++i) per[i] = i;
		do {
			fact++;
			for(int i = 1; i < n; ++i) {
				if(abs(per[i] - per[i-1]) == 1) goto out;
			}
			// for(int i : per) cout << i << " ";
			// cout << endl;
			total++;
out:;
		} while(next_permutation(per.begin(), per.end()));
		cout.precision(4);
		cout << n << ": \t" << total % 5 << "\t\t" << total / (double) fact;
		cout << "\t\t" << total - fact * 2 / 15 << endl;
		// cout << total / (double) fact << endl;
		// cout << total/2 << endl;
	}
	*/
}
