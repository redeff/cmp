#include <bits/stdc++.h>
using namespace std;

struct Circle {
	complex<double> center;
	double rad;
	bool sign;
};

pair<double, double> inter(Circle c, double l) {
	double x = c.center.real() - l;
	double dd = c.rad * c.rad - x * x;
	double d = 0.0;
	if(dd >= 0.0) d = sqrt(dd);
	return {c.center.imag() - d, c.center.imag() + d};
}

double sq(double r) { return r * r; }

pair<double, double> inter(Circle a, Circle b) {
	if(abs(a.center - b.center) > a.rad + b.rad) return {-2000.0, -2000.0};
	// |p - c1| = |p - c2|
	// |px - c1x, py - c1y| = |px - c2x, py - c2y|
	// c1x2 - c1x px + c1y2 - c1y py = c2x2 - c2x px + c2y2 - c2y py
	double d = norm(a.center - b.center);
	double k = 0.25 * sqrt((sq(a.rad + b.rad) - d) * (d - sq(a.rad - b.rad)));
	double f = 0.5 * (a.center.real() + b.center.real())
		+ 0.5 * (b.center.real() - a.center.real()) * (sq(a.rad) - sq(b.rad)) / d;
	double v = 2.0 * (b.center.imag() + a.center.imag()) * k / d;

	return {f - v, f + v};
}

int main() {
	int testcase;
	cin >> testcase;
	
	for(int test = 0; test < testcase; ++test) {
		int n;
		cin >> n;
		vector<Circle> ns;
		for(int i = 0; i < n; ++i) {
			double x, y, r, w;
			cin >> x >> y >> r >> w;
			ns.push_back(Circle {.center={x, y}, .rad=r-w, .sign=false});
			ns.push_back(Circle {.center={x, y}, .rad=r+w, .sign=true});
		}

		n *= 2;

		vector<double> critical;
		for(int i = 0; i < n; ++i) {
			critical.push_back(ns[i].center.real() + ns[i].rad);
			critical.push_back(ns[i].center.real() - ns[i].rad);
			for(int j = 0; j < i; ++j) {
				// cerr << "AAAAH" << endl;
				auto p = inter(ns[i], ns[j]);
				if(p.first != -2000.0) {
					critical.push_back(p.first);
					critical.push_back(p.second);
				}
			}
		}
		sort(critical.begin(), critical.end());
		double area = 0.0;
		for(int i = 1; i < critical.size(); ++i) {
			double lo = critical[i-1];
			double hi = critical[i];
			double mid = (lo + hi) / 2.0;
			// cerr << lo << " critical " << hi << endl;
			
			vector<pair<double, int>> is;
			for(int i = 0; i < n; ++i) {
				auto p = inter(ns[i], mid);
				if(p.first != ns[i].center.imag()) {
					is.emplace_back(p.first, i);
					is.emplace_back(p.second, -i -1);
				}
			}

			sort(is.begin(), is.end());
			int depth = 0;
			for(auto p : is) {
				int index = p.second < 0 ? - p.second - 1 : p.second;
				int pre = depth;
				depth += (ns[index].sign != (p.second < 0)) ? 1 : -1;
				double mul = depth > 0 && pre > 0 ? 0.0 : (depth == 0 ? -1.0 : 1.0);
				
				double le = p.second < 0 ? inter(ns[index], lo).first :
					inter(ns[index], lo).second;
				double ri = p.second < 0 ? inter(ns[index], hi).first :
					inter(ns[index], hi).second;

				complex<double> c1 {lo, le};
				c1 -= ns[index].center;
				complex<double> c2 {hi, ri};
				c2 -= ns[index].center;

				c2 /= c1 / abs(c1);
				// if(p.second >= 0) c2 = conj(c2);
				// c1 /= c1 / c1.abs();
				// cerr << mul << endl;
				// cerr << area << endl;
				double angle = abs(arg(c2));
				if(p.second >= 0) angle *= -1;
				// cerr << "index " << index << endl;
				// cerr << "arg " << arg(c2) << endl;
				// cerr << "leri " << le << " " << ri << endl;
				double delta = 0.0;
				delta -= 0.5 * mul * norm(c2) * (angle - sin(arg(c2)));
				delta += mul * (le + ri) * 0.5 * (hi - lo);
				// cerr << "delta " << delta << endl;
				area += delta;
			}
		}
		/*
		for(double l = -2000.0; l <= 2000.0; l += 0.05) {
			vector<pair<double, int>> s;
			for(As as : ns) {
				auto p = inter(as.x, as.y, as.r1, l);
					s.emplace_back(p.first, -1);
					s.emplace_back(p.second, 1);
				p = inter(as.x, as.y, as.r2, l);
					s.emplace_back(p.first, 1);
					s.emplace_back(p.second, -1);
			}
			sort(s.begin(), s.end());
			int depth = 0;
			double now = 0.0;
			for(int i = 1; i < s.size(); ++i) {
				depth += s[i-1].second;
				if(depth > 0) now += s[i].first - s[i-1].first;
			}
			total += (now + pre) / 2.0;
			prepre = pre;
			pre = now;
		}

		cout << total * 0.05 << endl;
		*/
		cout << area << endl;
	}
}
