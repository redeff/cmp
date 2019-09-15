#include "cycle.h"

int n;
int pos;

// door 0 is in [a, a + n/2]
bool isin(int a) {
	a -= pos;
	a %= n;
	a += n;
	a %= n;
	pos += a;
	pos %= n;
	return jump(a);
}

void escape(int _n) {
	n = _n;
	pos = 0;
	int pos = 0;

	int hi = n;
	int lo = 1;
	while(hi - lo > 1) {
		int mid = (hi + lo) / 2;
		if(isin(mid)) {
			lo = mid;
		} else {
			hi = mid;
		}
	}
	isin(lo);
}
