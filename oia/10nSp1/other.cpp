#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
unordered_map<ll, ll> ft;

const ll INF = 30000000ll;

#define cin cina
#define cout couta

int main() {
	ifstream cin("sumo.in");
	ofstream cout("sumo.out");
	ll n;
	cin >> n;
	vector<pair<ll, ll>> ns(n);
	for(auto &x : ns) cin >> x.first >> x.second;

	for(auto & x : ns) {
		x.first++;
		x.second++;
		
		for(ll i = x.first; i < INF; i += i & -i) {
			for(ll j = x.second; j < INF; j += j & -j) {
				ft[i * INF + j] += 1;
			}
		}
	}

	for(auto x : ns) {
		ll total = 0;
		for(ll i = x.first; i; i -= i & -i) {
			for(ll j = x.second; j; j -= j & -j) {
				total += ft[i * INF + j];
			}
		}
		cout << total - 1 << endl;
	}
}
