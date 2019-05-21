#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Node {
	ll pre;
	ll suf;
	ll sum;
	ll mx;
};

Node operator+(Node a, Node b) {
	Node res;
	res.pre = max(a.pre, a.sum + b.pre);
	res.suf = max(b.suf, a.suf + b.sum);
	res.mx = max(max(a.mx, b.mx), a.suf + b.pre);
	res.sum = a.sum + b.sum;

	return res;
}

Node from(ll val) {
	ll b = max(val, 0ll);
	return Node {b, b, val, b};
}

Node id = Node {0, 0, 0, 0};

int n;
vector<Node> build(vector<Node> leaves) {
	n = leaves.size();
	vector<Node> out(2 * n + 10);
	for(int i = 0; i < n; ++i) {
		out[n + i] = leaves[i];
	}
	for(int i = n-1; i > 0; --i) {
		out[i] = out[i<<1] + out[i<<1|1];
	}
	return out;
}

void update(vector<Node> &st, int p, Node val) {
	for(st[p += n] = val; p > 1; p >>= 1) st[p>>1] = st[p&(~1)] + st[p|1];
}

Node query(vector<Node> &st, int l, int r) {
	Node resl = id, resr = id;
	for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) resl = resl + st[l++];
		if (r&1) resr = st[--r] + resr;
	}
	return resl + resr;
}

int main() {
	int m;
	cin >> n >> m;
	vector<Node> ns(n);
	for(Node &no : ns) {
		ll i;
		cin >> i;
		no = from(i);
	}

	auto st = build(ns);
	for(int i = 0; i < m; ++i) {
		int ind;
		ll x;
		cin >> ind >> x;
		--ind;
		update(st, ind, from(x));
		cout << query(st, 0, n).mx << "\n";
	}
}
