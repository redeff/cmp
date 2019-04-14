#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x;
	double y;
};

struct Line {
	Point p;
	Point v;
};

Point rot(Point p) {
	return {p.y, -p.x};
}

Point operator-(Point a, Point b) {
	return {a.x - b.x, a.y - b.y};
}

Point operator+(Point a, Point b) {
	return {a.x + b.x, a.y + b.y};
}

bool parr(Line a, Line b) {
	return abs(b.v.x * a.v.y - b.v.y * a.v.x) < 1e-12;
}

double norma(Point p) {
	double r = p.x * p.x + p.y * p.y;
	return r;
}

Point nor(Point p) {
	double r = sqrt(p.x * p.x + p.y * p.y);
	return {p.x / r, p.y / r};
}

Point inter(Line a, Line b) {
	double bet = ((a.p.x - b.p.x) * a.v.y - (a.p.y - b.p.y) * a.v.x) / (b.v.x * a.v.y - b.v.y * a.v.x);
	return {b.v.x * bet + b.p.x, b.v.y * bet + b.p.y};
}

Point operator*(double d, Point p) {
	return {d * p.x, d * p.y};
};

double area(Point p, Point q) {
	return p.x * q.y - q.x * p.y;
}

int main() {
	int n;
	double r;
	cin >> n >> r;
	vector<Point> ns(n);
	for(Point &p : ns) cin >> p.x >> p.y;
	vector<Line> ls(n);
	for(int i = 0; i < n; ++i) {
		int prv = i == 0 ? n-1 : i-1;
		Point v = ns[i] - ns[prv];
		Point p = ns[prv] + r * rot(nor(v));
		ls[i] = Line {p, v};
	}

	vector<Point> all;
	for(int i = 0; i < n; ++i) for(int j = 0; j < i; ++j) {
		if(!parr(ls[i], ls[j])) {
			Point p = inter(ls[i], ls[j]);
			// cerr << p.x << " ~ " << p.y << endl;
			for(Line l : ls) {
				double d = area(p - l.p, l.v) / sqrt(norma(l.v));
				// cerr << d << endl;
				// cerr << area(p - l.p, l.v) << endl;
				// cerr << l.p.x << " " << l.p.y << " -- " << l.v.x << " " << l.v.y << endl;
				if(d < -1e-12) goto out;
			}
			all.push_back(p);
			goto end;
out: /*cerr << "fail" << endl*/;
end:;
		}
	}

	// for(Point p : all) cerr << p.x << " " << p. y << endl;
	double dist = 0.0;
	Point resa = {1.0, 1.0};
	Point resb = {1.0, 1.0};
	for(int i = 0; i < all.size(); ++i) for(int j = 0; j < i; ++j) {
		Point p = all[i];
		Point q = all[j];
		if(norma(p - q) > dist) {
			dist = norma(p - q);
			resa = p;
			resb = q;
		}
	}
	cout << resa.x << " " << resa.y << " " << resb.x << " " << resb.y << endl;
}
