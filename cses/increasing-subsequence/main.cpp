#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin >> n;
	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<ll> dp;
	for(ll i : ns) {
		auto it = lower_bound(dp.begin(), dp.end(), i);
		if(it == dp.end()) dp.push_back(i);
		else *it = min(*it, i);
	}

	cout << dp.size() << endl;
}
