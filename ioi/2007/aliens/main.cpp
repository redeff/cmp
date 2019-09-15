#include <bits/stdc++.h>
using namespace std;

int n;
bool query(int x, int y) {
	if(1 <= x && x <= n && 1 <= y && y <= n) {
		cout << "examine " << x << " " << y << endl;
		string s;
		cin >> s;
		return s == "true";
	} else return false;
}

int bin(int lo, int hi, int y) {
	// invariante: assert(query(hi, y) && !query(lo, y))
	while(abs(hi - lo) > 1) {
		int mid = (hi + lo) / 2;
		if(query(mid, y)) hi = mid;
		else lo = mid;
	}
	return lo;
}

int main() {
	int x, y;
	cin >> n >> x >> y;
	int lo = bin(-1, x, y);
	int hi = bin(n+1, x, y);
	// hi & lo esta'n en el borde de un cuadrado,
	// entonces M = d, M = d
}
