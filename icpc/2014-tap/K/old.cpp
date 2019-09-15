#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;

struct Treap {
	int size;
	ull wei;
	char val;
	bool inv;
	Treap *ch[2];
};

Treap* att(Treap* treap, int i) {
	assert(treap != nullptr);
	if(treap->inv) return treap->ch[1-i];
	else return treap->ch[i];
}

void setatt(Treap* treap, int i, Treap* val) {
	assert(treap != nullptr);
	if(treap->inv) treap->ch[1-i] = val;
	else treap->ch[i] = val;
}

Treap* create(char val) {
	Treap* out = new Treap;
	out->ch[0] = nullptr;
	out->ch[0] = nullptr;
	out->size = 1;
	out->wei = (ull(rand()) << 32ll) ^ ull(rand());
	out->val = val;
	out->inv = false;
	return out;
}

int size(Treap *treap) {
	if(treap == nullptr) return 0;
	else return treap->size;
}

Treap* join(Treap* a, Treap* b) {
	if(a == nullptr) return b;
	if(b == nullptr) return a;
	Treap* out = new Treap;

	if(a->wei < b->wei) {
		*out = *a;
		setatt(out, 1, join(att(a, 1), b));
	} else {
		*out = *b;
		setatt(out, 0, join(a, att(b, 1)));
		// out->ch[0] = join(a, b->ch[0]);
	}
	out->size = size(att(out, 0)) + size(att(out, 1)) + 1;
	return out;
}

pair<Treap*, Treap*> split(Treap* treap, int index) {
	cerr << index << " " << size(treap) << endl;
	assert(index <= size(treap));
	assert(size(treap) == size(att(treap, 0)) + size(att(treap, 1)) + 1);
	if(treap == nullptr) return {nullptr, nullptr};
	if(index <= size(att(treap, 0))) {
		cerr << 0 << endl;
		auto p = split(att(treap, 0), index);
		return {p.first, join(p.second, att(treap, 1))};
	} else {
		cerr << 1 << endl;
		auto p = split(att(treap, 1), index - size(att(treap, 0)));
		return {join(att(treap, 0), p.first), p.second};
	}
}

/*
pair<Treap*, Treap*> extr(Treap* treap, int a, int b) {
	assert(a < b);
	auto p = split(treap, a);
	auto q = split(p.second, b-a);
	return {join(p.first, q.second), q.first};
}

Treap* inser(Treap* treap, Treap* oth, int index) {
	auto p = split(treap, index);
	return join(p.first, join(oth, p.second));
}
*/

Treap* swp(Treap* treap, int a, int b, int c, int d) {
	assert(a < b);
	assert(b < c);
	assert(c < d);
	
	auto p = split(treap, d);
	auto q = split(p.first, c);
	auto r = split(q.first, b);
	auto s = split(r.first, a);

	Treap* out[5] = {s.first, s.second, r.second, q.second, p.second};
	if(out[1] != nullptr) out[1]->inv = !out[1]->inv;
	if(out[3] != nullptr) out[3]->inv = !out[3]->inv;

	return join(out[0], join(out[3], join(out[2], join(out[1], out[4]))));
}

void collect(Treap* treap, string &s) {
	if(treap == nullptr) return;
	collect(att(treap, 0), s);
	s.push_back(treap->val);
	collect(att(treap, 1), s);
}

int main() {
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
