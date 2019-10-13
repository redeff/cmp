#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;

// a(b + c) = ab + ab
// a + min(b, c) = min(a+b, a+c)

vector<ll> merg(vector<ll> as, vector<ll> bs) {
	// out[i] = min_j as[j] + bs[i-j]
	// as, bs increasing
	int a = int(as.size());
	int b = int(bs.size());

	// Convex
	forn(i, a-2) assert(as[i+2] + as[i] >= 2*as[i+1]);
	forn(i, b-2) assert(bs[i+2] + bs[i] >= 2*bs[i+1]);

	int c = a+b-1;
	vector<ll> cs(c);
	forn(k, c) {
		// 0 <= k - lo < b
		int lo = max(0, k - b);

		// k - hi >= 0
		int hi = min(a, k);

		while(hi - lo > 1) {
			int mid = (hi+lo)/2;
			ll val = as[mid+1] + bs[k-mid-1] - as[mid] - bs[k-mid];
			if(val < 0) lo = mid;
			else hi = mid;
		}

		cs[k] = as[hi] + bs[hi];
	}

	// forn(k, c-2) assert(cs[k+2] + cs[k] >= 2*cs[k+1]);
	return cs;
}

vector<ll> mx(vector<ll> as, vector<ll> bs, vector<ll> cs) {
	if(as.size() < bs.size()) swap(as, bs);
	if(as.size() < cs.size()) swap(as, cs);
	int n = int(as.size());
	vector<ll> out(n);
	forn(i, n) {
		out[i] = as[i];
		if(i < bs.size()) out[i] = min(out[i], bs[i]);
		if(i < cs.size()) out[i] = min(out[i], cs[i]);
	}
	return out;
}

struct Dp {
	vector<ll> m[2][2];
};

// vector<pair<int, int>> conv = {{0,0}, {1,0}, {0,1}};
Dp operator+(Dp a, Dp b) {
	Dp out;
	forn(s, 2) forn(e, 2) {
		out.m[s][e] = mx(
			merg(a.m[s][0], b.m[0][e]),
			merg(a.m[s][0], b.m[1][e]),
			merg(a.m[s][1], b.m[0][e])
		);
	}
	return out;
}

Dp single(ll a) {
	Dp out;
	out.m[0][0] = {0, a};
	out.m[0][1] = {0};
	out.m[1][0] = {0};
	out.m[1][1] = {0};
	return out;
}

Dp dupl(ll a, ll b) {
	Dp out;
	out.m[0][0] = {0, max(a, b)};
	out.m[0][1] = {0, a};
	out.m[1][0] = {0, b};
	out.m[1][1] = {0};
	return out;
}

Dp rec(ll *arr, int n) {
	assert(n > 0);
	if(n == 1) return single(arr[0]);
	if(n == 2) return dupl(arr[0], arr[1]);
	int h = n/2;
	return rec(arr, h) + rec(arr+h, n-h);
}

int main() {
	int n, k;
	cin >> n >> k;
	
	vector<ll> ns(n);
	for(ll & i : ns) cin >> i;

	Dp res = rec(&ns[0], n);
	cout << res.m[0][0][k] << endl;
}
