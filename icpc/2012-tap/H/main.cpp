#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;

/*
struct Rat {
	ll a;
	ll b;
};
*/

struct Line {
	ld l;
	ld c;
	ld eval(ld x) {
		return l*x + c;
	}
};

Line operator-(Line a, Line b) {
	return Line {a.l - b.l, a.c - b.c};
}

ld inter(Line a, Line b) {
	if(abs(a.l - b.l) < eps) return -12893;
	return (b.c - a.c) / (a.l - b.l);
}

bool operator<(Line a, Line b) {
	return make_pair(a.l, a.c) < make_pair(b.l, b.c);
}

bool ord(Line a, Line b) {
	if(abs(a.l - b.l) < eps) return true;
	return a.eval(inter(a, b)) >= 0;
	// return a.l * (b.c - a.c) / (a.l - b.l) + a.c >= 0;
}

Line through(ld a, ld b, ld c, ld d) {
	Line res;
	res.l = (a - c) / (b - d);
	res.c = a - res.l * a;
	return res;
}

vector<Line> chull(vector<Line> &ns) {
	sort(ns.begin(), ns.end());

	vector<Line> out;
	for(Line l : ns) {
		int n = out.size();
		while(n > 1 && ord(out[n-2] - l, out[n-1] - l)) out.pop_back();
		out.push_back(l);
	}

	return out;
}

int main() {
	int n;
	cin >> n;

	vector<int> cents(n);
	vector<pair<Line, Line>> lines(n);
	for(int i = 0; i < n; ++i) {
		int a, c, h;
		cin >> a >> b >> h;
		cents[i] = a + b;
		ld cen = (a + c) / 2.0l;
		lines[i].first = through(a, 0, c, h);
		lines[i].second = through(c, h, b, 0);
	}

	vector<int> sorted = cents;
	sort(sorted.begin(), sorted.end());
	for(int i = 1; i < n; ++i) {
		vector<Line> ls;
		for(int i = 0; i < n; ++i)
			if(cents[i] <= sorted[i]) ls.push_back(lines[i].first);
			else ls.push_back(lines[i].second);

		auto ns = chull(ls);
		for(Line l : ns) {
			cerr << l.l << " " << l.c << endl;
		}
	}
}
