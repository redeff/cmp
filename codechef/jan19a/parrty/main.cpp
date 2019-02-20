#include <bits/stdc++.h>
using namespace std;

typedef unordered_map<long long int, int> Fenwick;
const int MAX = 200100;
const int BASE = 300100;

struct Party {
	vector<pair<int, int>> v;
	int num;
	bool can;
};

int get_ft (int a, int b, Fenwick &ft){
	if(a > b) swap(a, b);
	a += 10;
	b += 10;
	int v = 0;
	for (int x = a; x; x -= x & -x)
		for (int y = b; y; y -= y & -y)
			v += ft[BASE * x + y];

	return v;
}

int get_range(int a1, int b1, int a2, int b2, Fenwick &ft) {
	return get_ft(b1, b2, ft) - get_ft(a1 - 1, a2 - 1, ft);
}

void set_ft (int a, int b, int v, Fenwick &ft){
	if(a > b) swap(a, b);
	a += 10;
	b += 10;
	for (int x = a; x < MAX; x += x & -x)
		for (int y = b; y < MAX; y += y & -y)
			ft[BASE * x + y] += v;
}

void bigs(vector<Party> &ns, vector<pair<int, int>> enemies) {
	vector<vector<pair<int, bool>>> sweep(MAX);
	for(int i = 0; i < ns.size(); ++i) {
		for(pair<int, int> p: ns[i].v) {
			sweep[p.first].push_back(make_pair(i, true));
			sweep[p.second + 1].emplace_back(i, false);
			// cerr << "--" << i << endl;
		}
	}

	vector<vector<int>> compr(MAX);
	for(int i = 0; i < enemies.size(); ++i) {
		compr[enemies[i].first].push_back(i);
		compr[enemies[i].second].push_back(i);
	}

	vector<vector<bool>> graph(ns.size(), vector<bool>(enemies.size(), false));
	vector<bool> curr(ns.size(), false);

	/*
	for(auto p : enemies) {
		cerr << p.first << ", " << p.second << endl;
	}
	*/

	for(int i = 0; i < MAX; ++i) {
		for(pair<int, bool> p : sweep[i]) {
			curr[p.first] = p.second;
		}

		for(int j = 0; j < ns.size(); ++j) if(curr[j]) {
			// if( compr[i].size() > 0)
				// cerr << ":" << j << endl;
			for(int k : compr[i]) {
				// cerr << k << endl;
				if(graph[j][k]) {
					ns[j].can = false;
				} else {
					graph[j][k] = true;
					// cerr << i << " " << j << " " << k << endl;
				}
			}
		}
	}
}

void smalls(vector<Party> &ns, Fenwick &ft) {
	for(int i = 0; i < ns.size(); ++i) {
		for(int j = 0; j < ns[i].v.size(); ++j) {
			for(int k = 0; k < j; ++k) {
				auto pa = ns[i].v[j];
				auto pb = ns[i].v[k];
				if(get_range(pa.first, pa.second, pb.first, pb.second, ft) > 0) ns[i].can = false;
			}
		}
	}
}

void testcase() {
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> enemies;
	Fenwick ft;
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		enemies.emplace_back(a, b);
		set_ft(a, b, 1, ft);
	}

	int q;
	cin >> q;
	vector<Party> parties(q);
	for(int i = 0; i < q; ++i) {
		int k;
		cin >> k;
		parties[i].num = i;
		parties[i].can = true;
		for(int j = 0; j < k; ++j) {
			int a, b;
			cin >> a >> b;
			parties[i].v.push_back(make_pair(a, b));
		}
	}

	sort(parties.begin(), parties.end(), [&](auto a, auto b) {return b.v.size() < a.v.size(); } );

	int l = min(q, 1000); // sqrt decomposition

	vector<Party> small;
	vector<Party> big;

	while(parties.size() > l) {
		small.push_back(parties.back());
		parties.pop_back();
	}
	big = parties;

	bigs(big, enemies);
	smalls(small, ft);

	vector<pair<int, bool>> res;
	for(Party p : big) res.emplace_back(p.num, p.can);
	for(Party p : small) res.emplace_back(p.num, p.can);
	sort(res.begin(), res.end());
	for(auto r : res) if(r.second) cout << "YES" << endl; else cout << "NO" << endl;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i) testcase();
}

