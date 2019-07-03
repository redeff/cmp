#include <bits/stdc++.h>
using namespace std;

class EvilCakeCutter {
public:
	double successProbability(int w, int h, int a, int b) {
		if(w <= 2*a && h <= 2*b) return 0.0;
		if(w <= 2*a) {
			swap(w, h);
			swap(a, b);
		}
		if(w >= 3*a || h >= 3*b) return 1.0;
		if(h <= 2*b) {
			return 1.0 - double(3*a - w) / double(w - a);
		}
		int dx = 3*a - w;
		int dy = 3*b - h;
		return 1.0 - double(dx) * double(dy) / double(w-a) / double(h-b);
	}
};
