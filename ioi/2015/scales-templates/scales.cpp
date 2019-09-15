#include "scales.h"
#include <bits/stdc++.h>
using namespace std;

void init(int T) {
	/* ... */
}

void my_sort(vector<int> &ns) {
	assert(ns.size() == 4);
	int t = getHeaviest(ns[0], ns[1], ns[2]);
	if(ns[0] != t) swap(*find(ns.begin(), ns.end(), t), ns[0]);
	t = getMedian(ns[0], ns[1], ns[3]);
	if(t == ns[0]) ns.insert(ns.begin(), ns[3]);
	else if(t == ns[1]) ns.insert(ns.begin() + 2, ns[3]);
	else if(t == ns[3]) ns.insert(ns.begin() + 1, ns[3]);
	else assert(false);
	ns.pop_back();

	int p = ns.back();
	ns.pop_back();
	assert(ns.size() == 3);
	t = getNextLightest(ns[0], ns[1], ns[2], p);
	ns.insert(find(ns.begin(), ns.end(), t) + 1, p);
}

void orderCoins() {
	/* ... */
	int a = getHeaviest(1, 2, 3);
	int b = getHeaviest(4, 5, 6);
	vector<int> ns;
	for(int i = 1; i <=6; ++i) if(i != a && i != b) ns.push_back(i);
	my_sort(ns);
	if(ns.back() <= 3) swap(a, b);
	int t = getNextLightest(ns[0], ns[1], ns[2], a);
	int index = find(ns.begin(), ns.end(), t) - ns.begin();
	assert(index < 3);
	++index;
	if(index == 3) index = 0;
	cerr << t << endl;
	ns.insert(ns.begin() + index, a);

	t = getNextLightest(ns[0], ns[1], ns[2], b);
	index = find(ns.begin(), ns.end(), t) - ns.begin();
	++index;
	if(index == 3) index = 0;
	ns.insert(ns.begin() + index, b);
	reverse(ns.begin(), ns.end());
	answer(&ns[0]);
}
