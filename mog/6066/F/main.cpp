#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long long int ll;
ll inf = 33333333333333333;

int main() {
	int n, k;
	cin >> n >> k;

	vector<ll> ns(n+2);
	forn(i, n) cin >> ns[i+1];
	ns[0] = inf;
	ns[n+1] = inf;

	vector<int> nxt(n+2);
	vector<int> prv(n+2);

	forn(i, n+2) nxt[i] = i+1;
	forn(i, n+2) prv[i] = i-1;

	vector<ll> vals = ns;

	set<pair<ll, int>> s;
	forn(i, n+2) s.insert({vals[i], i});

	ll total = 0;
	forn(ajsdh, k) {
		int i = s.begin()->second;
		int pr = prv[i];
		int nx = nxt[i];
		// cerr << i << endl;
		/*
		for(int j = 0; j < n+2; j = nxt[j]) {
			cerr << prv[j] << " <- " << j << " -> " << nxt[j] << endl;
		}
		*/
		s.erase({vals[i], i});
		s.erase({vals[pr], pr});
		s.erase({vals[nx], nx});

		total += vals[i];
		vals[pr] += vals[nx] - vals[i];
		s.insert({vals[pr], pr});
		nxt[pr] = nxt[nx];
		if(nxt[nx] < n+2) prv[nxt[nx]] = pr;
	}

	vector<bool> used(n+2, false);
	for(int i = 0; i < n+2; i = nxt[i]) {
		// cerr << prv[i] << " <- " << i << " -> " << nxt[i] << endl;
		for(int j = i; j < nxt[i]; ++j) {
			used[j] = i%2 != j%2;
		}
	}

	cout << total << endl;
	ll sum = 0;
	forn(i, n) if(used[i+1]) {
		cout << i+1 << " ";
		sum += ns[i+1];
	}

	cout << endl;
	assert(total == sum);
}
