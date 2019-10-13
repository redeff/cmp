#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

/*
struct Per {
	vector<int> per;
	vector<int> inv;
	int n;

	Per(vector<int> ns) {
		n = ns.size();
		per = ns;
		inv = vector<int>(n);
		forn(i, n) {
			assert(per[i] < n);
			inv[per[i]] = i;
		}
	}

	int left;
	int right;
}
*/

vector<int> inv_ino;

struct Tree {
	Tree *left;
	Tree *right;
	int index;
};

void traverse(Tree *t, vector<int> &pre, vector<int> &pos, vector<int> &ino) {
	if(t == nullptr) return;
	pre.push_back(t->index);
	traverse(t->left, pre, pos, ino);
	ino.push_back(t->index);
	traverse(t->right, pre, pos, ino);
	pos.push_back(t->index);
}

Tree *build(int a, int b, int c, vector<int> &pre, vector<int> &ino) {
	if(c <= 0) return nullptr;
	int root = inv_ino[pre[a]];
	Tree *left = build(a+1, b, root-b, pre, ino);
	Tree *right = build(a+root+1-b, root+1, c+b-root-1, pre, ino);
	Tree *res = new Tree;
	res->left = left;
	res->right = right;
	res->index = pre[a];
	return res;
}

int main() {
	int n;
	cin >> n;

	vector<int> pre(n);
	vector<int> pos(n);
	vector<int> ino(n);

	inv_ino = vector<int>(n);

	forn(i, n) {
		cin >> pre[i];
		pre[i]--;
	}
	forn(i, n) {
		cin >> pos[i];
		pos[i]--;
	}
	forn(i, n) {
		cin >> ino[i];
		ino[i]--;
		inv_ino[ino[i]] = i;
	}

	Tree *t = build(0, 0, n, pre, ino);
	vector<int> cpre;
	vector<int> cpos;
	vector<int> cino;
	traverse(t, cpre, cpos, cino);
	if(cpre == pre && cpos == pos && cino == ino) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}
