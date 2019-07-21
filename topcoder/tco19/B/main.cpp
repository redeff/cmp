#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

#define CLASS_NAME EllysIncrements
#define FUN_NAME getMin

const ll MAXN = 2e6;

const ll inf = 1e9;

void part(vector<ll> &ns) {
	ll n = ns.size();
	for(ll i = 1; i < n; ++i) ns[i] = min(ns[i-1]+1, ns[i]);
	for(ll i = n-2; i >= 0; --i) {
		ns[i] = min(ns[i], ns[i+1]);
	}
}

struct CLASS_NAME {
	int FUN_NAME(vector<int> ns) {
		vector<bool> isprime(MAXN, true);
		isprime[0] = false;
		isprime[1] = false;
		for(ll p = 2; p < MAXN; ++p) if(isprime[p]) {
			for(ll k = 2*p; k < MAXN; k += p) isprime[k] = false;
		}

		vector<ll> primes;
		for(ll p = 2; p < MAXN; ++p) if(isprime[p]) primes.push_back(p);

		vector<ll> dp(MAXN, inf);
		dp[0] = 0;
		part(dp);
		ll n = ns.size();
		for(ll i = 0; i < n; ++i) {
			for(ll j = 0; j < MAXN; ++j) {
				ll p = ns[i] + j;
				if(p < MAXN && isprime[p]) {
					// ndp[j] = dp[j];
				} else {
					dp[j] = inf;
				}
			}
			part(dp);
		}
		return dp[0];
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
