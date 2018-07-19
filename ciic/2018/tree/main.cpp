#include <bits/stdc++.h>
using namespace std;

struct Node {
	vector<Node> cs;
	bool black;
	int num;
};

Node compress(Node t) {
	vector<Node> ncs;
	for(int i = 0; i < t.cs.size(); ++i) {
		// t.cs[i] = compress(t.cs[i]);
		Node temp = compress(t.cs[i]);
		if(temp.black) {
			t.num += temp.num;
			for(auto c : temp.cs) {
				ncs.push_back(c);
			}
		} else {
			ncs.push_back(temp);
		}
	}
	t.cs = ncs;
	return t;
}

int main() {
	int n, p, k;
	cin >> n >> p >> k;

	// Colors
	vector<bool> cs(n);
	int bl;
	for(int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		cs[i] = tmp < p;
		if(cs[i]) bl = i;
	}

	vector<vector<int>> tree(n);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	vector<bool> seen(n);
	vector<int> parent(n);
	function<void(int)> root = [&](int k) {
		seen[k] = true;
		vector<int> ntreek;
		for(int i : tree[k]) {
			if(!seen[k]) ntreek.push_back(i);
			else parent[k] = i;
		}
		swap(tree[k], ntreek);
	};
	root(bl);

	function<Node(int)> treefy = [&](int k) -> Node {
		Node n;
		for(int c : tree[k]) {
			n.cs.push_back(treefy(c));
		}
		n.black = cs[k];
	};

	for(int i = 0; i < n; ++i) {
		cerr << i << ": ";
		for(auto c : tree[n]) cerr << c << " ";
		cerr << endl;
	}

	Node t = treefy(bl);
	t = compress(t);
}
