#include <bits/stdc++.h>
using namespace std;

struct Circ {
	int dir;
	int pos;
	int rad;
};

vector<Circ> read_circ() {
	int n;
	cin >> n;
	vector<Circ> res(n);
	string s;
	cin >> s;
	int dir = (s == "N") ? 1 : -1;

	int len = 0;
	for(Circ &c : res) {
		cin >> c.rad;
		c.pos = len + c.rad;
		len += 2*c.rad;
		c.dir = dir;
		dir *= -1;
	}

	return res;
}

double river;

double sq(double f) {
	return f*f;
}

double join_at(Circ a, Circ b, double x) {
	if(abs(x - a.pos) > a.rad + 1e-5 || abs(x - b.pos) > b.rad + 1e-5)
		return river;

	// cerr << " pos " << a.pos << endl;
	double ah = a.dir * sqrt(max(sq(a.rad) - sq(x - a.pos), 0.0));
	double bh = b.dir * sqrt(max(sq(b.rad) - sq(x - b.pos), 0.0));

	return river + ah - bh;
}

double join(Circ a, Circ b) {
	double total = river;
	total = min(total, join_at(a, b, a.pos - a.rad));
	total = min(total, join_at(a, b, a.pos + a.rad));
	total = min(total, join_at(a, b, b.pos - b.rad));
	total = min(total, join_at(a, b, b.pos + b.rad));
	double d = a.rad * a.dir - b.rad * b.dir;
	if(d != 0.0) {
		double g = (a.pos * a.rad * a.dir - b.pos * b.rad * b.dir) / d;
		total = min(total, join_at(a, b, g));
	}

	return total;
}

int main() {
	while(cin >> river && river != -1) {
		auto as = read_circ();
		auto bs = read_circ();
		double best = river;
		for(auto a : as) for(auto b : bs) best = min(best, join(a, b));
		best += 1e-5;
		cout.precision(2);
		cout << fixed;
		cout << round(best * 100.0) / 100.0 << endl;
		// cout << join_at(as[0], bs[0], 1) << endl;
	}
}
