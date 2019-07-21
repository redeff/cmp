#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	vector<string> ns(n);
	for(string & s : ns) cin >> s;

	struct Trie {
		int ch[2];
		vector<int> nodes;
		Trie () {
			ch = {-1, -1};
			nodes = {};
		}
	};

	vector<Trie> trie {Trie()};

	auto ins(int node, vector<bool> s) {
		int i = 0;
		for(bool b : s) {
			if(trie[i].ch[b] == -1) {
				trie[i].ch[b] = trie.size();
				trie.emplace_back();
			}
			i = trie.back();
		}
		if()
	}
	vector<vector<int>> graph;

}
