#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define cin cina
#define cout couta

int main() {
	ifstream cin("sumo.in");
	ofstream cout("sumo.out");
	ll n;
	cin >> n;
	vector<pair<ll, ll>> ns(n);
	for(auto &p : ns) cin >> p.first >> p.second;

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int a, int b) {return ns[a] < ns[b];});

	const int BOUND = 20000000;
	vector<ll> ft(BOUND, 0);
	vector<ll> res(n);
	for(int index = 0; index < n; ++index) {
		int i = ord[index];
		int total = 0;
		for(int x = ns[i].second + 1; x; x -= x & -x) {
			total += ft[x];
		}
		res[i] = total;
		for(int x = ns[i].second + 1; x < BOUND; x += x & -x) {
			ft[x] += 1;
		}
	}

	for(ll r : res) cout << r << endl;
}
