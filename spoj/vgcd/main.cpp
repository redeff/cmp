#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forz(i, z, n) for(int i = z; i < int(n); ++i)
using namespace std;

typedef long long int ll;
typedef long double ld;
ll base = 1e7;
ll baselog = 7;
struct Big {
	vector<ll> dig;
	Big(){}
	Big(int n) {
		dig = {n};
		norm();
	}
	int size() {
		return dig.size();
	}
	void norm() {
		forn(i, dig.size()-1) {
			dig[i+1] += dig[i] / base;
			dig[i] %= base;
		}
		while(!dig.empty() && dig.back() == 0) dig.pop_back();
	}

	string print() {
		norm();
		if(dig.size() == 0) return "0";
		string res;
		// reverse(dig.begin(), dig.end());
		bool fst = true;
		forn(i, dig.size()) {
			string ds = to_string(dig[i]);
			reverse(ds.begin(), ds.end());
			if(i != dig.size()-1)
				while(ds.size() < baselog) ds.push_back('0');
			for(char c : ds) res.push_back(c);
		}
		reverse(res.begin(), res.end());
		return res;
	}
};

Big operator*(Big a, Big b) {
	int n = a.size() + b.size() + 1;
	Big res;
	res.dig = vector<ll>(n, 0);

	forn(i, a.size()) forn(j, b.size()) {
		res.dig[i+j] += a.dig[i] * b.dig[j];
	}
	res.norm();
	return res;
}

Big operator+(Big a, Big b) {
	Big res;
	int n = max(a.size(), b.size()) + 1;
	res.dig = vector<ll>(n, 0);
	forn(i, a.size()) res.dig[i] += a.dig[i];
	forn(i, b.size()) res.dig[i] += b.dig[i];
	res.norm();
	return res;
}

struct Matrix {
	Big inner[2][2];
};

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	forn(i, 2) forn(j, 2) c.inner[i][j] = Big(0);
	forn(i, 2) forn(j, 2) forn(k, 2)
		c.inner[i][j] = c.inner[i][j] + a.inner[i][k] * b.inner[k][j];
	return c;
}

ll guess_fib(string s) {
	// cerr << s << " ";
	ld phi = (1.0 + sqrt(5.0))/2.0;
	ld guess = log(10.0) / log(phi) * ld(s.size() - 1);
	while(s.size() > 3) s.pop_back();
	while(s.size() < 3) s.push_back('0');
	int mant = stoi(s);
	// cerr << mant << " ";
	guess += log(mant / 100.0 * sqrt(5)) / log(phi);
	// cerr << guess << " ";
	int res = round(guess) + 0.5;
	// cerr << res << endl;
	return res;
}

Big nth_fib(ll k) {
	Matrix acc;
	acc.inner[0][0] = 1;
	acc.inner[1][0] = 0;
	acc.inner[0][1] = 0;
	acc.inner[1][1] = 1;

	Matrix pos;
	pos.inner[0][0] = 1;
	pos.inner[1][0] = 1;
	pos.inner[0][1] = 1;
	pos.inner[1][1] = 0;

	while(k != 0) {
		if(k%2) {
			acc = acc * pos;
		}
		pos = pos * pos;
		k /= 2;
	}

	return acc.inner[0][1];
}

ll gcd(ll a, ll b) {
	while(a != 0) {
		b %= a;
		swap(a, b);
	}
	return b;
}

int main() {
	/*
	forz(i, 2, 501) {
		string s = nth_fib(i).print();
		assert(guess_fib(s) == i);
		// cout << i << " \t" << nth_fib(i).print() << endl;
	}
	return 0;
	*/
	int n;
	cin >> n;
	forn(slajdhf, n) {
		string as, bs;
		cin >> as >> bs;
		ll a = guess_fib(as);
		ll b = guess_fib(bs);
		cout << nth_fib(gcd(a, b)).print() << endl;
	}
}
