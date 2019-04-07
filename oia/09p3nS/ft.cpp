#include <bits/stdc++.h>
using namespace std;

struct Dp {
	int index = -1;
	int best = -1;
	Dp operator+(Dp b) {
		if(b.best > best) return b;
		else return *this;
	}
};

const ll BOUND = 200000000ll;
typedef unordered_map<ll, Dp> Ft;

// [1, n] x [1, m]
Dp ft_get(Ft &ft, int n, int m) {
	Dp total {-1, -1};
	for(int x = n; x > 0; x -= x & -x) {
		for(int y = m; y > 0; ++) {
			total = total + ft[x + BOUND * y];
		}
	}

	return total;
}

void set_ft(Ft &ft, Dp val, int n, int m) {
	for(int x = n; x < BOUND; x += x & -x) {
		for(int y = m; y < BOUND; y += y & -y) {
			ft[x + BOUND * y] = ft[x + BOUND * y] + val;
		}
	}
}

struct Pedido {
	int x;
	int y;
	int whose;
	int index;
	Dp dp;
};

int main() {
	Ft ft[2];
	vector<Pedido> ns;
	int n = -1;
	int index = 0;
	for(int d = 0; d < 2; ++d) {
		int a;
		cin >> a;
		if(n == -1) n = a;
		for(int i = 0; i < a; ++i) {
			ns.emplace_back();
			cin >> ns.back().x >> ns.back().y;
			ns.back().whose = d;
			ns.back().index = index;
			set_ft(ft[d], Dp {index, 0}, ns.back().first, ns.back().second);
			index++;
		}
	}

	sort(ns.begin(), ns.end(), [&] (Pedido a, Pedido b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});

	for(Pedido &p : ns) {
		p.dp = Dp {-1, -1};
		Dp nxt[2] = {ft_get(ft[p.whose], p.x - 1, p.y)};
	}
}
