#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

struct Pedido {
	int b;
	int e;
	int n[2];
	pair<int, int> dp;
	int best;
};

int main() {
#ifndef LOLOLOL
#define cin blabla
#define cout djhfa
	ifstream cin("mercanchifle.in");
	ofstream cout("mercanchifle.out");
#endif
	int n[2];
	vector<Pedido> ns[2];
	for(int i = 0; i < 2; ++i) {
		cin >> n[i];
		ns[i] = vector<Pedido>(n[i]);
		for(Pedido &p : ns[i]) {
			cin >> p.b >> p.e;
			p.e++;
		}
	}

	vector<int> orde[2];
	vector<int> ordb[2];
	for(int i = 0; i < 2; ++i) {
		orde[i] = vector<int>(n[i]);
		iota(orde[i].begin(), orde[i].end(), 0);
		sort(orde[i].begin(), orde[i].end(), [&](int a, int b) {
			return ns[i][a].e < ns[i][b].e;
		});
		for(int j = 1; j < n[i]; ++j) {
			ns[i][orde[i][j-1]].n[0] = j < n[i] ? orde[i][j] : n[i];
		}

		ordb[i] = vector<int>(n[i]);
		iota(ordb[i].begin(), ordb[i].end(), 0);
		sort(ordb[i].begin(), ordb[i].end(), [&](int a, int b) {
			return ns[i][a].b < ns[i][b].b;
		});
	}

	for(int d = 0; d < 2; ++d) {
		int curr = 0;
		for(Client i : orde[d]) {
			while(curr < n[1-d] && ns[d][i].e > ns[1-d][ordb[1-d][curr]].b) curr++;
			ns[d][i].n[1] = ordb[1-d][curr];
		}
	}

#define inx(p) ns[(p).first][(p).second]

	vector<pair<int, int>> all;
	for(int d = 0; d < 2; ++d) for(int i = 0; i < n[d]; ++i) all.emplace_back(d, i);
	sort(all.begin(), all.end(), [&] (pi a, pi b) {
		return inx(a).e > inx(b).e;
	});

	for(auto p : all) {
		int d = p.first;
		int i = p.second;
		Pedido &c = ns[d][i];
		c.best = 0;
		c.dp.second = n[d];
		c.dp.first = d;
		for(int f = 0; f < 2; ++f) {
			if(c.n[f] != n[d^f]) {
				// cerr << "FUA" << endl;
				if(ns[d^f][c.n[f]].best > c.best) {
					// cerr << "BAB" << endl;
					c.best = ns[d^f][c.n[f]].best;
					c.dp.first = d^f;
					c.dp.second = c.n[f];
				}
			}
		}
		c.best += 1;
		// cerr << c.b << " " << c.e << " " << c.best << endl;
	}

	auto p = *max_element(all.begin(), all.end(), [&] (pi a, pi b) {
		return inx(a).best < inx(b).best;
	});

	vector<int> res[2];
	res[p.first].push_back(p.second);
	while(inx(p).dp.second < n[inx(p).dp.first]) {
		p = inx(p).dp;
		res[p.first].push_back(p.second);
	}

	cout << res[0].size() + res[1].size() << endl;
	for(int d = 0; d < 2; ++d) {
		for(int i :  res[d]) cout << i+1 << " ";
		cout << endl;
	}
}
