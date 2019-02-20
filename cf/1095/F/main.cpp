#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Uf {
	int dad;
	int wei;
};

int repr(int node, vector<Uf> &uf) {
	int dad = node;
	while(uf[dad].dad != dad) dad = uf[dad].dad;
	
	int t = node;
	while(t != dad) {
		int d = uf[t].dad;
		uf[t].dad = dad;
		t = d;
	}

	return dad;
}

void join(int a, int b, vector<Uf> &uf) {
	// a = repr(a, uf);
	// b = repr(b, uf);
	if(uf[a].wei < uf[b].wei) swap(a, b);
	if(uf[a].wei == uf[b].wei) uf[a].wei++;
	uf[b].dad = a;
}

vector<Uf> init(int n) {
	vector<Uf> uf(n);
	for(int i = 0; i < n; ++i) {
		uf[i].dad = i;
		uf[i].wei = 0;
	}

	return uf;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<ll> weis(n);
	for(int i = 0; i < n; ++i) {
		cin >> weis[i];
	}

	vector<int> per(n);
	// weis[per[0..i]] ordered
	for(int i = 0; i < n; ++i) per[i] = i;
	sort(per.begin(), per.end(), [&] (int a, int b) { return weis[a] < weis[b]; });
	vector<int> inv(n);
	for(int i = 0; i < n; ++i) inv[per[i]] = i;

	sort(weis.begin(), weis.end());

	priority_queue<pair<pair<ll, bool>, pair<int, int>>> pq;

	for(int i = 0; i < m; ++i) {
		int x, y;
		ll w;
		cin >> x >> y >> w;
		x--;
		y--;
		pq.push({{-w, false}, {inv[x], inv[y]}});
	}
	per.resize(0);
	per.shrink_to_fit();
	inv.resize(0);
	inv.shrink_to_fit();
	pq.push({{-2ll * weis[0], true}, {0, 0}});

	int comp = n;
	auto uf = init(n);
	ll total = 0;
	while(comp > 1) {
		auto t = pq.top();
		pq.pop();

		int a = t.second.first;
		int b = t.second.second;

		int ra = repr(a, uf);
		int rb = repr(b, uf);
		if(ra != rb) {
			join(ra, rb, uf);
			comp--;
			total -= t.first.first;
		}

		if(t.first.second) {
			if(b + 1 < n)
				pq.push({{-weis[a] - weis[b + 1], true}, {a, b + 1}});

			if(a + 1 < n)
				pq.push({{-weis[a + 1] - weis[b], true}, {a + 1, b}});
		}
	}

	cout << total << endl;
}
