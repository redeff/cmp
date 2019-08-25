#include <bits/stdc++.h>
#define fore(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

const int BOUND = 1e6;

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<pair<bool, int>>> events(2 * BOUND + 1);
	fore(i, 0, n) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		if(y1 > y2) swap(y1, y2);
		if(x1 > x2) swap(x1, x2);
		x1 += BOUND;
		x2 += BOUND;
		y1 += BOUND;
		y2 += BOUND;

		events[x1].emplace_back(true, y1);
		events[x1].emplace_back(true, y2);
		events[x2].emplace_back(false, y1);
		events[x2].emplace_back(false, y2);
	}

	multiset<int> all;
	ll total = 0;
	for(auto & v : events) {
		for(auto p : v) {
			if(p.first) {
				all.insert(p.second);
			} else {
				auto it = all.find(p.second);
				assert(it != all.end());
				all.erase(it);
				// all.erase(p.second);
			}
		}
		assert(all.size() % 2 == 0);
		if(!all.empty()) {
			total += *all.rbegin() - *all.begin();
		}
	}

	assert(all.empty());

	cout << total << endl;
}
