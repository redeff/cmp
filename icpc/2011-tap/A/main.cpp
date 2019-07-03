#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

unordered_map<ll, ll> dp;
vector<ll> ns;

ll comb(ll a, ll b, ll c, ll d) {
	ll l = 10;
	return a + ((b + ((c + (d << l)) << l)) << l);
}

ll f(int a, int b, int c, int d, int n) {
	if(n == (int)ns.size()-1) return 1;
	ll h = comb(a, b, c, d);
	if(dp.count(h)) return dp[h];
	ll res = 0;
	if(ns[n] + ns[b] < 2*ns[a] && 2*ns[n] > ns[a]) res += f(n, a, c, d, n+1);
	if(ns[n] + ns[c] < 2*ns[d] && 2*ns[n] > ns[d]) res += f(a, b, d, n, n+1);
	dp[h] = res;
	return res;
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		ns = vector<ll>(n);
		dp = unordered_map<ll, ll>();
		for(ll &i : ns) cin >> i;
		sort(ns.begin(), ns.end());
		ll prod = 1;
		ll eq = 1;
		for(int i = 1; i < n; ++i) {
			if(ns[i] == ns[i-1]) {
				eq++;
			} else {
				eq = 1;
			}
			if(eq > 2) {
				cout << 0 << endl;
				goto end;
			}
			prod *= eq;
		}
		reverse(ns.begin(), ns.end());
		ns.push_back(-1);

		cout << f(0, n, n, 0, 1)/prod << endl;

end:;
	}
}
