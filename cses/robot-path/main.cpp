#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int MAXN = 1e7;
const int MAXM = 1e7;

ll comb(int a, int b) {
	return (ll(a) << 30ll) + ll(b);
}

int getFT (int a, int b, unrdered_map<ll, int> &ft){
	a += 5e6;
	b += 5e6;
	int v = 0;
	for (int x = a; x; x -= x & -x)
		for (int y = b; y; y -= y & -y)
			v += FT[comb(x, y)];
	return v;
}
void setFT (int a, int b, int v, unordered_map<ll, int> &ft){
	a += 5e6;
	b += 5e6;
	for (int x = a; x < MAXN; x += x & -x)
		for (int y = b; y < MAXM; y += y & -y)
			FT[comb(x, y)] += v;
}

int main() {
	int n;
	cin >> n;

	unordered_map<ll, int> hor;
	unordered_map<ll, int> ver;

	int x = 0;
	int y = 0;
	for(int i = 0; i < n; ++i) {
		string dir;
		int len;
		cin >> dir >> len;
		int z(x), w(y);
		switch(dir) {
			case "U": w += dir; break;
			case "D": w -= dir; break;
			case "R": z += dir; break;
			case "L": z -= dir; break;
		}

		switch(dir) {
			case "U": case "D":
				 "U": case "D":
		}
	}
}
