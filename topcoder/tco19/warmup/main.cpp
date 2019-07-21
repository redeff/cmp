#include <bits/stdc++.h>
using namespace std;

struct WarmupWithTwins {
	int determineTwinsAge(vector<int> ages) {
		if(ages.size() == 1) return ages[0];
		multiset<int> a;
		for(int i : ages) a.insert(i);
		for(int i : ages) if(a.count(i) > 1) return i;
		return -1;
	}
};

#ifdef YOP
#endif
