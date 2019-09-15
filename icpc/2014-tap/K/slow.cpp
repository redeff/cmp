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

vector<Treap> heap;

void prop(Treap *treap) {
	if(treap != nullptr && treap->inv) {
		treap->inv = false;
		treap->val++;
		if(treap->val == 'z'+1) treap->val = 'a';
		swap(treap->ch[0], treap->ch[1]);
		if(treap->ch[0] != nullptr) treap->ch[0]->inv = !treap->ch[0]->inv;
		if(treap->ch[1] != nullptr) treap->ch[1]->inv = !treap->ch[1]->inv;
	}
}

Treap* create(char val) {
	heap.emplace_back();
	Treap* out = &heap[heap.size()-1];
	// Treap* out = new Treap;
	out->ch[0] = nullptr;
	out->ch[1] = nullptr;
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
	prop(a);
	prop(b);
	heap.emplace_back();
	// Treap* out = new Treap;
	Treap* out = &heap[heap.size()-1];

	if(a->wei < b->wei) {
		*out = *a;
		out->ch[1] = join(a->ch[1], b);
		// setatt(out, 1, join(a->ch[1], b));
	} else {
		*out = *b;
		out->ch[0] = join(a, b->ch[0]);
		// out->ch[0] = join(a, b->ch[0]);
	}
	out->size = size(out->ch[0]) + size(out->ch[1]) + 1;
	return out;
}

pair<Treap*, Treap*> split(Treap* treap, int index) {
	if(treap == nullptr) return {nullptr, nullptr};
	prop(treap);
	// cerr << index << " " << size(treap) << endl;
	// assert(index <= size(treap));
	// assert(size(treap) == size(treap->ch[0]) + size(treap->ch[1]) + 1);
	if(index == size(treap->ch[0])) {
		return {treap->ch[0], join(create(treap->val), treap->ch[1])};
	}
	else if(index < size(treap->ch[0])) {
		// cerr << 0 << endl;
		auto p = split(treap->ch[0], index);
		// assert(size(p.first) == index);
		return {p.first, join(p.second, join(create(treap->val), treap->ch[1]))};
	} else {
		// cerr << 1 << endl;
		auto p = split(treap->ch[1], index - size(treap->ch[0]) - 1);
		return {join(treap->ch[0], join(create(treap->val), p.first)), p.second};
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
	/*
	assert(a <= b);
	assert(b <= c);
	assert(c <= d);
	assert(d <= size(treap));
	*/
	
	auto p = split(treap, d);
	// assert(size(p.first) == d);
	auto q = split(p.first, c);
	// assert(size(q.first) == c);
	auto r = split(q.first, b);
	// assert(size(r.first) == b);
	auto s = split(r.first, a);
	// assert(size(s.first) == a);

	Treap* out[5] = {s.first, s.second, r.second, q.second, p.second};
	if(out[1] != nullptr) out[1]->inv = !out[1]->inv;
	if(out[3] != nullptr) out[3]->inv = !out[3]->inv;

	return join(out[0], join(out[3], join(out[2], join(out[1], out[4]))));
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
	heap.reserve(10000000);
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
		heap.clear();
	}
}
