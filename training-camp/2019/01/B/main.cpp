#include <bits/stdc++.h>
using namespace std;

enum Query {
	A,
	B,
	Id,
	Inv
};

Query operator*(Query a, Query b) {
	if(a == A) return a;
	if(a == B) return a;
	if(a == Id) return b;
	if(a == Inv) {
		if(b == Id) return Inv;
		if(b == Inv) return Id;
		if(b == A) return B;
		if(b == B) return A;
	}
}

pair<int, int> operator*(Query a, pair<int, int> t) {
	int sum = t.first + t.second;
	if(a == Id) return t;
	if(a == Inv) return {t.second, t.first};
	if(a == A) return {sum, 0};
	if(a == B) return {0, sum};
}

pair<int, int> operator+(pair<int, int> a, pair<int, int> b) {
	return {a.first + b.first, a.second + b.second};
}

struct Node {
	pair<int, int> val;
	Query fun;
};

int BOUND = 1500000;
Node st[BOUND];

void prop(int node) {
	int a = 2*node+1;
	int b = 2*node+2;
	st[node].val = st[node].fun * st[node].val;
	if(a < BOUND) {
		st[a].fun = st[node].fun * st[a].fun;
	}
	if(b < BOUND) {
		st[b].fun = st[node].fun * st[b].fun;
	}
	st[node].fun = Id;
}

pair<int, int> sum(int node, int mx, int a, int b) {
	prop(node);
	if(a <= 0 && b >= mx) {
		return st[node].val;
	}
}

int main() {
	
}
