#include <bits/stdc++.h>
using namespace std;

struct DevuAndRabbitNumbering {
	string canRenumber(vector<int> ns) {
		sort(ns.begin(), ns.end());
		int n = int(ns.size());
		for(int i = 1; i < n; ++i) {
			for(int j = 0; j < 2; ++j) {
				if(ns[i] <= ns[i-1]) ns[i]++;
			}
			if(ns[i] <= ns[i-1]) return "cannot";
		}
		return "can";
	}
};
