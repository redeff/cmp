// https://www.spoj.com/problems/CMEXPR/
#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
#define fore(i, z, n) for(int i = z; i < n; ++i)
using namespace std;

struct Expr {
	char type;
	char val;
	vector<pair<bool, Expr*>> ch;
};

string s;
vector<int> p;

bool additive(int l, int r) {
	for(int i = l; i < r; ++i) {
		if(s[i] == '(') {
			i = p[i];
		} else if(s[i] == '+' || s[i] == '-') {
			return true;
		}
	}
	return false;
}

bool letter(char c) {
	return 'a' <= c && c <= 'z';
}

Expr *parse(int l, int r) {
	// cerr << l << " " << r << endl;
	assert(r > l);
	if(s[l] == '(' && p[l] == r-1) {
		assert(s[r-1] == ')');
		return parse(l+1, r-1);
	}
	if(r-l == 1) {
		auto e = new Expr;
		e->type = 'v';
		e->val = s[l];
		e->ch = {};
		return e;
	}
	vector<pair<char, int>> ops;
	bool add = additive(l, r);
	ops.push_back({add?'+':'*',l-1});
	for(int i = l; i < r; ++i) {
		if(s[i] == '(') i = p[i];
		else if(false
				|| s[i] == '+'
				|| s[i] == '-'
				|| (!add && (false
						|| s[i] == '*'
						|| s[i] == '/'
						))
			) {
			ops.push_back({s[i], i});
		}
	}
	ops.push_back({'#', r});
	vector<pair<bool, Expr*>> es;
	forn(i, ops.size()-1) {
		bool positive = ops[i].first == '+' || ops[i].first == '*';
		es.push_back({positive, parse(ops[i].second+1, ops[i+1].second)});
	}
	auto e = new Expr;
	e->type = add ? 'a' : 'm';
	e->val = '#';
	e->ch = es;
	return e;
}

void normalize(Expr *e) {
	if(e->type == 'v') return;
	for(auto c : e->ch) normalize(c.second);
	vector<pair<bool, Expr*>> nor;
	for(auto c : e->ch) {
		Expr *ch = c.second;
		if(c.first && ch->type == e->type) {
			for(auto pr : ch->ch) nor.push_back(pr);
		} else nor.push_back(c);
	}
	e->ch = nor;
}

void print(Expr *e) {
	if(e->type == 'v') {
		cout << e->val;
		return;
	}
	if(e->type == 'm') cout << "[";
	else cout << "(";
	forn(i, e->ch.size()) {
		if(i != 0) cout << " ";
		if(!e->ch[i].first) cout << "-";
		print(e->ch[i].second);
	}
	if(e->type == 'm') cout << "]";
	else cout << ")";
}

void display(Expr *e, bool pr) {
	if(e->type == 'v') {
		cout << e->val;
		return;
	}
	if(pr) cout << "(";
	forn(i, e->ch.size()) {
		char oper[2][2] = {{'+', '-'}, {'*', '/'}};
		if(i != 0) cout << oper[e->type=='m'][!e->ch[i].first];
		bool nest = false;
		char th = e->ch[i].second->type;
		if(th == 'a' && e->type == 'm') nest = true;
		if(th == e->type && !e->ch[i].first) nest = true;
		display(e->ch[i].second, nest);
	}
	if(pr) cout << ")";
}

void matching() {
	p.resize(s.size());
	vector<int> prv;
	for(int i = s.size()-1; i >= 0; --i) {
		if(s[i] == ')') prv.push_back(i);
		if(s[i] == '(') {
			p[i] = prv.back();
			prv.pop_back();
		}
	}
}

int main() {
	int n;
	cin >> n;
	forn(askdjfhaksdf, n) {
		cin >> s;
		// cerr << s << endl;
		matching();
		auto e = parse(0, s.size());
		normalize(e);
		display(e, false);
		cout << endl;
	}
}
