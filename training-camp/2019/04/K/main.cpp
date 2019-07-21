#include <bits/stdc++.h>
using namespace std;

typedef long double lld;

// #define DBG(x) cerr << #x << ": " << x << endl;
#define DBG(x)

lld heron(lld a, lld b, lld c) {
	lld s = (a + b + c) / 2.0;
	lld res = sqrt(s * (s - a) * (s - b) * (s - c));
	// cerr << res << endl;
	return res;
}

lld circun(lld a, lld b, lld c) {
	lld area = heron(a, b, c);
	lld rad = a * b * c / (4.0 * area);
	// lld sina = 2 * b * c / area;
	// lld rad = 0.5 * a / sina;
	return rad;
}

lld cosa(lld a, lld b, lld c) {
	// a*a = b*b + c*c - 2bc cos a
	// cos a = (b*b + c*c - a*A) / (2*b*c)
	return (b*b + c*c - a*a) / (2*b*c);
}

lld height(lld ab, lld bc, lld ca, lld ad, lld bd, lld cd) {
	// lld area_abc = heron(ab, bc, ca);
	lld area_abd = heron(ab, ad, bd);
	lld hei_abd = 2.0 * area_abd / ab;
	lld s = sqrt(ad*ad - hei_abd*hei_abd);
	DBG(s);

	lld area_acd = heron(ca, ad, cd);
	lld hei_acd = 2.0 * area_acd / ca;
	lld t = sqrt(ad*ad - hei_acd*hei_acd);
	DBG(t);

	lld cos_a = cosa(bc, ab, ca);

	lld u = sqrt(t*t + s*s - 2*s*t*cos_a);
	DBG(u);

	lld d = 2.0 * circun(s, t, u);

	DBG(d);
	DBG(ad);
	lld res = sqrt(ad*ad - d*d);
	DBG(res);
	return res;
}

lld inrad(lld ab, lld bc, lld ca, lld ad, lld bd, lld cd) {
	lld area = heron(ab, bc, ca) + heron(ab, ad, bd) + heron(bc, bd, cd) + heron(ca, cd, ad);
	lld vol = 1.0/3.0 * height(ab, bc, ca, ad, bd, cd) * heron(ab, bc, ca);

	// 1/3 area * inrad = vol
	return 3.0 * vol / area;
}

int main() {
	int test;
	cin >> test;
	cout << fixed << setprecision(4);
	while(test --> 0) {
		lld ab, bc, ca, ad, bd, cd;
		cin >> ad >> bd >> cd >> ab >> ca >> bc;
		lld res = inrad(ab, bc, ca, ad, bd, cd);
		// cout << "total: " << res << endl;
		cout << res << endl;
	}
}
