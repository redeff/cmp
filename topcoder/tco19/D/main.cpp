#include <bits/stdc++.h>
using namespace std;

#define CLASS_NAME a
#define FUN_NAME b

struct CLASS_NAME {
	int FUN_NAME(vector<int> ages) {
		return -1;
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
