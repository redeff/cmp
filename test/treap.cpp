#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ll;

ll llrnd(){
	static std::random_device rd;
	static std::mt19937_64 eng;
	static int init = true;
	if(init) {
		init = false;
		eng = std::mt19937_64(rd());
	}

	std::uniform_int_distribution<ll> distr;
	return distr(eng);
}

template<class T>
struct Node {
	ll heap;
	T val;
	Node *ch[2];
};

template<class T>
Node<T> *single(T val) {
	auto n = new Node<T>;
	n->heap = llrnd();
	n->val = val;
	n->ch[0] = nullptr;
	n->ch[1] = nullptr;

	return n;
}

template<class T>
Node<T> *mrg_rec(Node<T> *nodes[2]) {
	if(nodes[0] == nullptr) return nodes[1];
	if(nodes[1] == nullptr) return nodes[0];
	int head = nodes[1]->heap < nodes[0]->heap;

	Node<T> *rec[2] = {nodes[0], nodes[1]};
	rec[head] = nodes[head]->ch[1-head];

	auto out = new Node<T>;
	out = nodes[head];
	out->ch[1-head] = mrg_rec(rec);

	return out;
}

template<class T>
Node<T> *mrg(Node<T> *a, Node<T>* b) {
	Node<T> *c[2] = {a, b};
	return mrg_rec(c);
}

template<class T>
pair<Node<T>*, Node<T>*> split(Node<T> *treap, T val) {
	if(treap == nullptr) return {nullptr, nullptr};
	auto out = new Node<T>;
	out = treap;

	int side = treap->val < val;
	auto oth = split(out->ch[side], val);
	out->ch[side] = nullptr;

	return side
		? make_pair(mrg(out, oth.first), oth.second)
		: make_pair(oth.first, mrg(oth.second, out))
		;
}

template<class T>
Node<T> *add(Node<T> *treap, T val) {
	pair<Node<T>*, Node<T>*> p = split(treap, val);
	return mrg(mrg(p.first, single(val)), p.second);
}

template<class T>
void print(Node<T> *treap, string level) {
	if(treap == nullptr) return;
	// cerr << "(";
	if(treap != nullptr) {
		level.push_back(' ');
		print(treap->ch[0], level);
		level.pop_back();

		cerr << level << treap->val << endl;

		level.push_back(' ');
		print(treap->ch[1], level);
		level.pop_back();
	}
	// cerr << ")";
}

int main() {
	Node<int> *t = nullptr;
	while(true) {
		int i;
		cin >> i;
		t = add(t, i);
		print(t, "");
	}
}
