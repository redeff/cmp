#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x;
	double y;
};

double dot(Point a, Point b) {
	return a.x*b.x + a.y*b.y;
}

double cross(Point a, Point b) {
	return a.x*b.y - a.y*b.x;
}

Point operator+(Point a, Point b) {
	return Point {a.x+b.x, a.y+b.y};
}

Point operator-(Point a, Point b) {
	return Point {a.x-b.x, a.y-b.y};
}

Point operator*(double lambda, Point a) {
	return Point {lambda*a.x, lambda*a.y};
}

Point rot(Point a) {
	return Point {a.y, -a.x};
}

Point inter(Point v, Point p, Point w, Point q) {
	// X | exists lambda, mu | lambda v + p = mu w + q = X
	// lv + p = mw + q
	// (lv + p) x w = (mw + q) x w
	// (lv + p) x w = q x w
	// lv x w + p x w = q x w
	// lv x w = (q - p) x w
	// l = (q - p) x w / (v x w)
	return cross(q - p, w) / cross(v, w) * v + p;
}

// Point lala = Point {8374.283, 11233.8374};

const double epsilon = 1e-6;
void caso(Point a, Point b, Point c, vector<Point> &out) {
		Point v = rot(b - a);
		Point d = 1.5*b - 0.5*a;

		Point w = rot(b - c);
		Point e = 0.5*b + 0.5*c;

		if(abs(cross(v, w)) < epsilon) {
			return;
		} else {
			Point q = inter(v, d, w, e);
			Point p = 2.0*b - q;
			Point s = 2.0*a - p;
			Point t = 2.0*c - q;
			// Point k = a+c-b;
			// Point r = 2.0*k - t;
			if((
						cross(s-p, p-q) < -epsilon &&
						cross(p-q, q-t) < -epsilon &&
						cross(q-t, t-s) < -epsilon &&
						cross(t-s, s-p) < -epsilon
				 ) || (
						cross(s-p, p-q) > epsilon &&
						cross(p-q, q-t) > epsilon &&
						cross(q-t, t-s) > epsilon &&
						cross(t-s, s-p) > epsilon
			)) {
				out.push_back(s);
				out.push_back(p);
				out.push_back(q);
				out.push_back(t);
				return;
				cout << "YES" << endl;
				cout
					<< s.x << " " << s.y << " " 
					<< p.x << " " << p.y << " "
					<< q.x << " " << q.y << " "
					<< t.x << " " << t.y << "\n";
					// << r.x << " " << r.y << endl;
			} else {
				return;
				cout << "NO\n\n";
			}
		}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int test;
	cin >> test;
	cout.precision(20);
	while(test --> 0) {
		Point a, b, c;
		cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
		vector<Point> res;
		caso(a, b, c, res);
		caso(a, c, b, res);
		caso(b, a, c, res);
		caso(b, c, a, res);
		caso(c, a, b, res);
		caso(c, b, a, res);
		if(res.size() == 0) {
			cout << "NO\n\n";
		} else {
			cout << "YES\n";
			for(int i = 0; i < 4; ++i) {
				cout << res[i].x << " " << res[i].y;
				if(i != 3) cout << " ";
				else cout << "\n";
			}
		}
	}
}
