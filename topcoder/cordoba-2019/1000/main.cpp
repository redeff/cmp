#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct EllysSuperMario {
	long long getMin(int N, int K, int F, int A, int B, int M) {
		ll n = ll(N);
		ll k = ll(K);
		ll f = ll(F);
		ll a = ll(A);
		ll b = ll(B);
		ll m = ll(M);

		deque<pair<ll, ll>> dp = {{0, -1}};
		ll price = f;
		for(ll i = 0; i < n+1; ++i) {
			while(i - dp.front().second > k) dp.pop_front();
			if(i == n) return dp.front().first;
			ll best = dp.front().first + price;
			while(dp.back().first >= best && !dp.empty()) dp.pop_back();
			dp.push_back({best, i});

			price = price * a + b;
			price %= m;
		}
		return ll(-1);
	}
};
