#include <bits/stdc++.h>
using namespace std;

double g = 9.8;
double d;
double v;

double f(double a) {
	return sqrt(v * v - a * a) * (a + sqrt(a * a + 2 * g * d)) / g;
}

int main() {
	while(cin >> v >> d && v != -1.0) {
		double lo = 0.0;
		double hi = v;

		while(hi - lo > 1e-9) {
			double a = (2.0 * lo + hi) / 3.0;
			double b = (lo + 2.0 * hi) / 3.0;
			if(f(a) < f(b)) lo = a;
			else hi = b;
		}

		double val = f(hi);
		cout.precision(6);
		cout << fixed << val << endl;
	}
}
