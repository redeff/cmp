#include <bits/stdc++.h>
using namespace std;

#define CLASS_NAME RealTaskWithTwins
#define FUN_NAME solve

struct CLASS_NAME {
	vector<int> FUN_NAME(vector<int> ages) {
		int mx = *max_element(ages.begin(), ages.end());
		multiset<int> a;
		for(int i : ages) a.insert(i);
		int total = 0;
		for(int i : ages) if(a.count(i) == 2) total++;
		if(ages.size() - total > 0) total += 2;
		return {mx, total/2};
	}
};

#ifdef YOP
int main() {
	CLASS_NAME test;

	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) cin >> i;

	cout << test.FUN_NAME(ns) << endl;
}
#endif
