#include <bits/stdc++.h>
using namespace std;

struct SumUnique {
	int getSum(vector<int> values) {
		sort(values.begin(), values.end());
		values.erase(unique(values.begin(), values.end()), values.end());
		// unordered_map<int> vls;
		// for(int v : values) vls.insert(v);
		int total = 0;
		for(int v : values) total += v;
		return total;
	}
};
