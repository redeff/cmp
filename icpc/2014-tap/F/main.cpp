#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < n; ++i)

typedef unsigned long long int ull;

ull modprod;
ull modinv;

ull inv(ull a) {
	assert(a % 2 == 1);
	ull x = a;
	forn(alksjdlkasjdf, 10) x = x * (2 - a*x);
	assert(x*a == 1);
	return x;
}

vector<int> inv_per(vector<int> ns) {
	int n = int(ns.size());
	vector<int> out(n);
	forn(i, n) out[ns[i]] = i;
	return out;
}

vector<string> layers;
vector<int> per;
vector<ull> hashes;

void cut() {
	int n = int(hashes.size());
	forn(i, n) {
		hashes[i] -= layers.back()[i];
		hashes[i] *= modinv;
	}
	layers.pop_back();

	auto perinv = inv_per(per);
	sort(per.begin(), per.end(), [&](int a, int b) {
		if(hashes[a] == hashes[b]) return a < b;
		else return perinv[a] < perinv[b];
	});
}

void add(string s) {
	int n = int(hashes.size());
	auto perinv = inv_per(per);
	sort(per.begin(), per.end(), [&](int a, int b) {
		if(hashes[a] == hashes[b]) {
			if(s[a] == s[b]) return a < b;
			else return s[a] < s[b];
		} else return perinv[a] < perinv[b];
	});

	layers.push_back(s);
	forn(i, n) {
		hashes[i] *= modprod;
		hashes[i] += layers.back()[i];
	}
}

int main() {
	int n, t;
	cin >> n >> t;
	layers = vector<string>(n, "");
	per = vector<int>(n);
	forn(i, n) per[i] = i;
	hashes = vector<ull>(n, 0);

	modprod = 93272934889ull;
	modinv = inv(modprod);

	while(t --> 0) {
		int c, p;
		string s;
		cin >> c >> s >> p;
		while(c --> 0) cut();
		add(s);
		cout << per[p-1]+1 << endl;
	}
}
