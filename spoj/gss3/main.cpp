#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Node {
	ll pre;
	ll suf;
	ll sum;
	ll mx;
	ll elem;
};

Node operator+(Node a, Node b) {
	Node res;
	res.pre = max(a.pre, a.sum + b.pre);
	res.suf = max(b.suf, a.suf + b.sum);
	res.mx = max(max(a.mx, b.mx), a.suf + b.pre);
	res.sum = a.sum + b.sum;
	res.elem = max(a.elem, b.elem);

	return res;
}

Node from(ll val) {
	ll b = max(val, 0ll);
	return Node {b, b, val, b, val};
}

const ll INF = 3333333333333ll;
Node id = Node {0, 0, 0, 0, -INF};

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
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	vector<Node> ns(n);
	for(Node &no : ns) {
		ll i;
		cin >> i;
		no = from(i);
	}

	auto st = build(ns);
	int m;
	cin >> m;
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a == 0) {
			update(st, b-1, from(c));
		} else {
			Node q = query(st, b-1, c);
			if(q.elem < 0) cout << q.elem;
			else cout << q.mx;
			cout << "\n";
			// cout << query(st, b-1, c).mx << endl;
		}
	}
}