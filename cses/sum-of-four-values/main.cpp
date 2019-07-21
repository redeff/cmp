// https://cses.fi/problemset/task/1642/
#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

typedef long long int ll;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n; ll x;
	cin >> n >> x;

	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	vector<pair<ll, pair<int, int>>> los;
	vector<pair<ll, pair<int, int>>> his;
	forn(i, n) forn(j, i) {
		los.emplace_back(ns[i] + ns[j], make_pair(j, i));
		his.emplace_back(ns[i] + ns[j], make_pair(i, j));
	}

	sort(los.begin(), los.end());
	sort(his.begin(), his.end());

	int lo = los.size() - 1;
	forn(hi, his.size()) {
		while(lo > 0 && los[lo].first + his[hi].first > x) lo--;
		auto a = his[hi].second;
		auto b = los[lo].second;
		if(los[lo].first + his[hi].first == x && a.first < b.first) {
			cout << a.first+1 << " " << a.second+1 << " " << b.first+1 << " " << b.second+1;
			return 0;
		}
	}

	cout << "IMPOSSIBLE" << "\n";
}
