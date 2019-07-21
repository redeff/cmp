#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double prec;

prec fact(ll n) {
	static vector<prec> dp = {1};
	while(dp.size() <= n) {
		dp.push_back(dp.back() * prec(dp.size()));
	}
	return dp[n];
}

prec choose(ll k, ll h) {
	return fact(k) / fact(h) / fact(k-h);
	/*
	for(ll i = 1; i <= k; ++i) {
		total *= prec(i);
	}

	for(ll i = 1; i <= h; ++i) total /= prec(i);
	for(ll i = 1; i <= k-h; ++i) total /= prec(i);

	// cerr << k << " " << h << " -> " << total << endl;
	return total;
	*/
}

prec prob(vector<ll> cota, ll k) {
	ll n = cota.size();
	// dp[i][j] == # ways putting j people in the last i..n slots
	vector<vector<prec>> dp(n+1, vector<prec>(k+1, 0));
	// for(int &i : dp.back()) i = 0;
	dp.back()[0] = 1;
	for(ll i = n-1; i >= 0; --i) {
		for(ll j = 0; j <= k; ++j) {
			for(ll h = 0; h <= min(cota[i], j); ++h) {
				dp[i][j] += choose(k - j + h, h) * dp[i+1][j - h];
			}
		}
	}

	// ll total = 0;
	// for(int i = 0; i <= k; ++i) total += dp[0][i];

	return dp[0][k];
}

int main() {
	ll k;
	ll n;
	cin >> k >> n;

	vector<ll> ns(n);
	for(ll &i : ns) cin >> i;

	// vector<ll> dp(k);
	prec pr = 0;
	prec total = 0;
	prec ex = 0;
	for(ll i = 0; i <= k; ++i) {
		vector<ll> cotas = ns;
		for(ll &p : cotas) p *= i;
		prec ways = prob(cotas, k);
		total += ways - pr;
		ex += (ways - pr) * i;
		pr = ways;
	}

	// cout << ex << " " << total << " " << pr << endl;
	cout.precision(20);
	cout << double(ex)/double(pr) << endl;
}
