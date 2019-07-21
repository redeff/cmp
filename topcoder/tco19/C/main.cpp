#include <bits/stdc++.h>
using namespace std;

#define CLASS_NAME EllysLightbulbs
#define FUN_NAME getMax

typedef long long int ll;

ll parse(string &s) {
	ll res = 0ll;
	for(char c : s) {
		res *= 2ll;
		res += c - '0';
	}
	return res;
}

vector<ll> ns;
int n;
bool can(ll target, ll reach, int i) {
	if(i >= n) return false;
	if(can(target, reach, i+1)) return true;
	if((target & reach & ns[i]) == 0) {
		return can(target, reach | ns[i], i+1);
	}
	return false;
}

struct CLASS_NAME {
	string FUN_NAME(int N, int L, vector<string> ss) {
		n = L;
		for(string &s : ss) ns.push_back(parse(s));
		random_shuffle(ns.begin(), ns.end());
		ll best = 0;
		string total;
		for(ll i = N-1; i >= 0; ++i) {
			if(can(best + (1ll << i), 0, 0)) {
				best += (1ll << i);
				total.push_back('1');
			} else {
				total.push_back('0');
			}
		}
		return total;
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
