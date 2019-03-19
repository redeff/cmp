#include <bits/stdc++.h>
using namespace std;

int main() {
	double v, h, g;
	g = 9.8;
	while(cin >> v >> h && v != -1.0) {
		double dist = sqrt(2 * g * h + v * v) * v / g;
		cout.precision(6);
		cout << fixed << dist << endl;
	}
}
