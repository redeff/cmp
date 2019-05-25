#include <bits/stdc++.h>
using namespace std;

int main() {
	long long k, n;
	long long prv = 0;
	vector<pair<long long, long long>> ns;
	while(cin >> k >> n) {
		ns.push_back({k, n});
		// cout << k << "\t" << (n - 2) << endl;
		// cout << n - prv * k << endl;
		// prv = n;
	}

	for(int i = ns.size(); i > 0; --i) {
		ns[i].second -= ns[i].first * ns[i-1].second;
	}
	for(int i = ns.size(); i > 0; --i) {
		ns[i].second -= (ns[i].first - 4) * ns[i-1].second;
	}

	for(auto p : ns) cout << p.second << endl;
}
