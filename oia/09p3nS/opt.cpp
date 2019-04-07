#include <bits/stdc++.h>
using namespace std;

struct Pedido {
	int start;
	int end;
	int index;
	Pedido* dp;
	int whose;
	int best;
};

#define twice(d) for(int (d) = 0; (d) < 2; ++(d))

int main() {
	vector<Pedido> ns[2];
	twice(d) {
		int n;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			ns[d].emplace_back();
			cin >> ns[d].back().start >> ns[d].back().end;
			ns[d].back().end++;
			ns[d].back().index = i;
			ns[d].back().whose = d;
			ns[d].back().dp = nullptr;
		}
	}

	twice(d) sort(ns[d].begin(), ns[d].end(), [&](Pedido a, Pedido b) {return a.start < b.start;});
	twice(d) for(int i = ns[d].size()-1; i >= 0; --i) {
		ns[d][i].best = 0;
		ns[d][i].dp = nullptr;

		if(i+1 < ns[d].size() && ns[d][i+1].best > ns[d][i].best) {
			ns[d][i].best = ns[d][i+1].best;
			ns[d][i].dp = &ns[d][i+1];
		}

		auto l = lower_bound(
			ns[1-d].begin(), ns[1-d].end(),
			Pedido {ns[d][i].end, -1, -1, nullptr},
			[&](Pedido a, Pedido b) {
				return a.start < b.start;
		});
		if(l != ns[1-d].end() && l->best > ns[d][i].best) {
			ns[d][i].best = l->best;
			int index = distance(ns[1-d].begin(), l);
			ns[d][i].dp = &ns[1-d][index];
		}
		ns[d][i].best++;
	}
	
	Pedido *mx = &ns[0][0];
	twice(d) for(Pedido &p : ns[d]) {
		if(mx->best <= p.best) mx = &p;
		cerr << p.best << " " << p.index << " " << p.whose << endl;
	}

	vector<int> res[2];
	while(mx != nullptr) {
		res[mx->whose].push_back(mx->index);
		mx = mx->dp;
	}
	cout << res[0].size() + res[1].size() << endl;
	twice(d) {
		for(int i : res[d]) cout << i << " ";
		cout << endl;
	}
};
