#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef LOLOLOL
	ifstream cin("autodromo.in");
	ofstream cout("autodromo.out");
#endif
	for(int g = 0; g < 2; ++g) {
		int n;
		cin >> n;
		pair<int, int> fst;
		pair<int, int> lst;
		cin >> fst.first >> fst.second;
		int dummy;
		for(int i = 0; i < n-2; ++i) cin >> dummy >> dummy;
		cin >> lst.first >> lst.second;
		// cerr << fst.first << fst.second << lst.first << lst.second << endl;
		assert(fst.first == lst.first || fst.second == lst.second);
	}
}
