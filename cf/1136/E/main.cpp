#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Tree {
	Tree *left;
	Tree *right;
	ll mn;
	ll mx;

	int lo;
	int hi;

	ll sum;

	bool lazy;
	bool value;

	void propagate() {
		if(this == nullptr) return;
		if(lazy) {
			mn = value;
			mx = value;
			sum = (hi - lo) * value;
			lazy = false;
			if(right != nullptr) {
				right->value = value;
				right->lazy = true;
			}
			if(left != nullptr) {
				left->value = value;
				left->lazy = true;
			}
		}
	}

	ll gt(int pos) {
		propagate();
		if(hi = lo + 1) return sum;
		else if(left == nullptr) return right->gt(pos);
		else if(left->hi > pos) return left->gt(pos);
		else return right->gt(pos);
	}

	void st(int _lo, ll val) {
		propagate();
		if(mn >= val) return;
		if(hi <= _lo) return;
		if(lo >= _lo && mx <= val) {
			lazy = true;
			value = val;
			propagate();
			return;
		}
		left->st(_lo, val);
		right->st(_lo, val);
		left->propagate();
		right->propagate();
		mn = left->mn;
		mx = right->mx;
		sum = left->sum + right->sum;
	}
	
	ll sums(int _lo, int _hi) {
		propagate();
		// if(this == nullptr) return 0;
		// if(hi = lo + 1) return sum;
		if(_hi <= lo) return 0;
		if(hi <= _lo) return 0;
		if(_lo <= lo && hi <= _hi) return sum;
		else {
			return right->sums(_lo, _hi) + left->sums(_lo, _hi);
		}
	}
};

Tree* build(int lo, int n) {
	if(n == 0) return nullptr;
	Tree* t = new Tree;
	Tree* left = build(lo, n/2);
	Tree* right = nullptr;
	if(n > 1) right = build(lo + n/2, n - n/2);

	t->sum = 0;
	t->lazy = false;
	t->mn = 0;
	t->mx = 0;

	return t;
}

void partial_sums(vector<ll> &v) {
	for(int i = 1; i < v.size(); ++i) {
		v[i] += v[i-1];
	}
}

int main() {
	int n;
	cin >> n;
	vector<ll> as(n);
	vector<ll> ks(n-1);
	for(ll & a : as) cin >> a;
	for(ll & k : ks) cin >> k;
	partial_sums(ks);

	for(int i = 1; i < n; ++i) as[i] -= ks[i-1];

	partial_sums(ks);


	int q;
	cin >> q;

	Tree* all = build(0, 100);
	for(int i = 0; i < n; ++i) {
		cerr << all->sum << endl;
		all->st(i, as[i]);
	}

	for(int i = 0; i < q; ++i) {
		string s;
		cin >> s;
		if(s == "+") {
			int i;
			ll x;
			cin >> i >> x;
			i--;
			all->st(i, all->gt(i) + x);
		}
		else {
			int l, r;
			cin >> l >> r;
			l--;
			cout << all->sums(l, r) + ks[r] - ks[l] << endl;
		}
	}
}
