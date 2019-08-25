#include <bits/stdc++.h>
using namespace std;

const int sigma = 'z' - 'a' + 1;

struct Trie {
	int sum[2];
	Trie *ch[sigma];
};

Trie *create() {
	auto t = new Trie;
	t->sum[0] = 0;
	t->sum[1] = 0;

	for(int i = 0; i < sigma; ++i) t->ch[i] = nullptr;
	return t;
}

void ins(Trie *trie, string &s, int pos) {
	trie->sum[pos]++;
	if(s.empty()) return;

	int last = s.back() - 'A';
	if(trie->ch[last] == nullptr) {
		trie->ch[last] = create();
	}

	s.pop_back();
	ins(trie->ch[last], s, pos);
}

int gt(Trie *trie) {
	if(trie == nullptr) return 0;
	int total = min(trie->sum[0], trie->sum[1]);
	for(int i = 0; i < sigma; ++i) total += gt(trie->ch[i]);
	return total;
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		Trie *trie = create();
		for(int i = 0; i < 2*n; ++i) {
			string name;
			cin >> name;
			reverse(name.begin(), name.end());
			ins(trie, name, i < n);
		}
		cout << gt(trie) - n << endl;
	}
}
