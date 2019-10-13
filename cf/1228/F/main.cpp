#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

int inf = 10000000;

typedef vector<vector<int>> Tree;

vector<int> depths(Tree &tree, int root) {
	int n = int(tree.size());
	vector<int> res(n);
	function<void(int, int, int)> dfs =
		[&](int node, int dad, int depth) {
			res[node] = depth;
			for(int ch : tree[node]) if(ch != dad) {
				dfs(ch, node, depth+1);
			}
		};
	dfs(root, root, 0);
	return res;
}

vector<int> centers(Tree &tree) {
	int n = int(tree.size());

	auto ds1 = depths(tree, 0);
	int a = max_element(ds1.begin(), ds1.end()) - ds1.begin();
	auto dsa = depths(tree, a);
	int b = max_element(dsa.begin(), dsa.end()) - dsa.begin();
	auto dsb = depths(tree, b);

	vector<int> res;
	forn(i, n) {
		if(dsa[i] + dsb[i] == dsa[b] && abs(dsa[i] - dsb[i]) <= 1) {
			res.push_back(i);
		}
	}
	assert(res.size() <= 2);
	assert(res.size() >= 1);
	return res;
}

struct Rooted {
	int index;
	vector<Rooted> ch;
};

int p;

bool isbin(Tree &tree, int root) {
	/*
	auto cs = center(tree);
	if(cs.size() != 0) return false;
	int root = cs[0];
	*/

	if(tree[root].size() != 2) return false;

	function<bool(int, int, int)> dfs =
		[&](int node, int dad, int depth) {
			if(tree[node].size() == 1) {
				if(depth != p) return false;
				else return true;
			} else if(tree[node].size() == 3) {
				for(int ch : tree[node]) {
					if(ch != dad) {
						if(!dfs(ch, node, depth+1)) return false;
					}
				}
				return true;
			} else return false;
			// assert(false);
			// return false;
		};
	
	for(int ch : tree[root]) if(!dfs(ch, root, 2)) return false;
	return true;
}

int calc(Tree &tree, int root) {
	int n = int(tree.size());
	if(tree[root].size() == 2) {
		int k = -1;
		forn(i, n) if(i != root) {
			if(tree[i].size() != 1 && tree[i].size() != 3) {
				if(k != -1) return -1;
				k = i;
			}
		}
		if(k == -1) return -1;
		

		if(tree[k].size() == 2) {
			Tree nt = tree;
			nt.emplace_back();
			nt[k].push_back(n);
			nt[n].push_back(k);
			if(isbin(nt, root)) return k;
			else return -1;
		} else if(tree[k].size() == 4) {
			forn(i, 4) forn(j, i) {
				Tree nt = tree;
				nt.emplace_back();
				int a = nt[k][i];
				int b = nt[k][j];
				swap(nt[k][i], nt[k].back());
				nt[k].pop_back();
				nt[k][j] = n;
				nt[n].push_back(k);
				nt[n].push_back(a);
				nt[n].push_back(b);
				*find(nt[a].begin(), nt[a].end(), k) = n;
				*find(nt[b].begin(), nt[b].end(), k) = n;
				if(isbin(nt, root)) return k;
			}
			return -1;
		} else return -1;
	} else if(tree[root].size() == 3) {
		int k = root;
		forn(i, 3) forn(j, i) {
			Tree nt = tree;
			nt.emplace_back();
			int a = nt[k][i];
			int b = nt[k][j];
			swap(nt[k][i], nt[k].back());
			nt[k].pop_back();
			nt[k][j] = n;
			nt[n].push_back(k);
			nt[n].push_back(a);
			nt[n].push_back(b);
			*find(nt[a].begin(), nt[a].end(), k) = n;
			*find(nt[b].begin(), nt[b].end(), k) = n;
			if(isbin(nt, root)) return k;
		}
		return -1;
	} else if(tree[root].size() == 1) {
		int k = root;
		Tree nt = tree;
		nt.emplace_back();
		nt[k].push_back(n);
		nt[n].push_back(k);
		if(isbin(nt, root)) return k;
		else return -1;
	} else return -1;
}

int main() {
	cin >> p;
	int n = (1 << p) - 2;
	Tree tree(n);

	forn(sdhf, n-1) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	vector<int> poss;
	for(int r : centers(tree)) {
		int k = calc(tree, r);
		if(k != -1) poss.push_back(k);
	}
	sort(poss.begin(), poss.end());
	unique(poss.begin(), poss.end());
	cout << poss.size() << endl;
	if(poss.size() != 0) {
		for(int i : poss) cout << i+1 << " ";
		cout << endl;
	}
}
