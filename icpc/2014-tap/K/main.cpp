#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

typedef unsigned long long int ll;

struct Treap {
	int size;
	char val;
	int op;
	ll wei;
	Treap *ch[2];
};

Treap* create(char c) {
	Treap* treap = new Treap;
	treap->size = 1;
	treap->val = c;
	treap->op = 0;
	treap->wei = (ll(rand()) << 32ll) | ll(rand());
	treap->ch[0] = nullptr;
	treap->ch[1] = nullptr;
	return treap;
}

int sigma = 'z' - 'a' + 1;
char step(char c, int i) {
	assert(i >= 0);
	int ch = c;
	assert(int('a') <= ch && ch <= int('z'));
	ch += i % sigma;
	while(ch > int('z')) ch -= sigma;
	assert(int('a') <= ch && ch <= int('z'));
	return ch;
}

void prop(Treap* treap) {
	if(treap != nullptr) {
		treap->val = step(treap->val, treap->op);
		if(treap->op % 2 == 1) swap(treap->ch[0], treap->ch[1]);
		forn(i, 2) if(treap->ch[i] != nullptr) treap->ch[i]->op += treap->op;
		treap->op = 0;
	}
}

int size(Treap *treap) {
	return treap == nullptr ? 0 : treap->size;
}

void upd(Treap* treap) {
	prop(treap);
	if(treap != nullptr) {
		treap->size = 1 + size(treap->ch[0]) + size(treap->ch[1]);
	}
}

Treap* join(Treap* a, Treap *b) {
	if(a == nullptr) return b;
	if(b == nullptr) return a;
	step(a->val, 0);
	prop(a);
	step(b->val, 0);
	prop(b);

	if(a->wei < b->wei) {
		// cerr << "1" << endl;
		a->ch[1] = join(a->ch[1], b);
		upd(a);
		return a;
	} else {
		// cerr << "0" << endl;
		b->ch[0] = join(a, b->ch[0]);
		upd(b);
		return b;
	}
}

pair<Treap*, Treap*> split(Treap *treap, int index) {
	if(treap == nullptr) {
		assert(index == 0);
		return {nullptr, nullptr};
	}
	prop(treap);
	assert(index <= size(treap));
	if(index <= size(treap->ch[0])) {
		Treap* ch = treap->ch[0];
		auto p = split(ch, index);
		treap->ch[0] = p.second;
		upd(treap);
		return {p.first, treap};
	} else {
		Treap* ch = treap->ch[1];
		auto p = split(ch, index - size(treap->ch[0]) - 1);
		treap->ch[1] = p.first;
		upd(treap);
		return {treap, p.second};
	}
}

/*
pair<Treap*, Treap*> split(Treap *treap, int index) {
	Treap tmp;
	tmp.ch[0] = nullptr;
	tmp.ch[1] = nullptr;

	Treap* left = &tmp;
	Treap* right = &tmp;

	int orig = index;
	while(treap != nullptr) {
		prop(treap);
		cerr << index << " " << size(treap) << endl;
		assert(index <= size(treap));
		if(index <= size(treap->ch[0])) {
			assert(right->ch[0] == nullptr);
			right->ch[0] = treap;
			treap = treap->ch[0];
			right->ch[0]->ch[0] = nullptr;
			// upd(right->ch[0]);
			// upd(right);
			right = right->ch[0];
		} else {
			index -= size(treap->ch[0])+1;

			assert(left->ch[1] == nullptr);
			left->ch[1] = treap;
			treap = treap->ch[1];
			left->ch[1]->ch[1] = nullptr;
			// upd(left->ch[1]);
			// upd(left);
			left = left->ch[1];
		}
	}
	assert(index == 0);
	assert(size(tmp.ch[1]) == orig);
	return {tmp.ch[1], tmp.ch[0]};
}
*/

Treap* swp(Treap* treap, int a, int b, int c, int d) {
	prop(treap);
	assert(a <= b);
	assert(b <= c);
	assert(c <= d);
	// cerr << size(treap) << " = " << d << endl;
	assert(d <= size(treap));
	
	auto p = split(treap, d);
	assert(size(p.first) == d);
	auto q = split(p.first, c);
	assert(size(q.first) == c);
	auto r = split(q.first, b);
	assert(size(r.first) == b);
	auto s = split(r.first, a);
	assert(size(s.first) == a);

	Treap* out[5] = {s.first, s.second, r.second, q.second, p.second};
	if(out[1] != nullptr) out[1]->op++;
	if(out[3] != nullptr) out[3]->op++;

	out[1] = join(out[1], out[4]);
	out[2] = join(out[2], out[1]);
	out[3] = join(out[3], out[2]);
	out[0] = join(out[0], out[3]);
	prop(out[0]);
	upd(0);
	return out[0];
}

void collect(Treap* treap, string &s) {
	if(treap == nullptr) return;
	prop(treap);
	collect(treap->ch[0], s);
	s.push_back(treap->val);
	collect(treap->ch[1], s);
}

int main() {
	srand(120374231);
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t --> 0) {
		string s;
		int n;
		cin >> s >> n;
		Treap* treap = nullptr;
		for(char c : s) treap = join(treap, create(c));
		for(int i = 0; i < n; ++i) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			--a; --c;
			treap = swp(treap, a, b, c, d);
		}

		string out;
		collect(treap, out);
		cout << out << endl;
	}
}
