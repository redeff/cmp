#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = int(z); i < int(n); ++i)
using namespace std;

// Logitud del máximo sufijo no trivial de s[0..i) que es también prefijo de s[0..i)
// out[0] = -1
vector<int> kmp(string s) {
	int n = int(s.size());
	vector<int> res(n+1);
	res[0] = -1;
	forn(i, 1, n+1) {
		int k = res[i-1];
		while(k != -1 && s[k] != s[i-1]) k = res[k];
		res[i] = k+1;
	}
	forn(i, 0, n+1) assert(res[i] < i);
	forn(i, 1, n+1) assert(res[i] >= 0);
	forn(i, 1, n+1) {
		forn(j, 0, res[i]) assert(s[j] == s[j + i - res[i]]);
	}
	return res;
}

// Máximo pref de s[i..n) que es pref de s[0..n)
vector<int> zarr(string s) {
	n = int(s.size());
	vector<int> z(n);
	int l = 0;
	int r = 0;
	forn(i, 1, n) {
		if (i > r) {
			l = i; r = i;
			while (r < n && s[r-l] == s[r]) r++;
			z[i] = r-l; --r;
		} else {
			int k = i-l;
			if (z[k] < r-i+1) z[i] = z[k];
			else {
				l = i;
				while (r < n && s[R-L] == s[r]) r++;
				z[i] = r-l;
				--r;
			}
		}
	}
	return z;
}

// Máximo suff de w que es suff de s[0..i)
vector<int> suff_end(string w, string s) {
	reverse(w.begin(), w.end());
	reverse(s.begin(), s.end());
	auto z = zarr(w + "$" + s);
	reverse(z.begin(), z.end());
	// z.pop_back();
	for(char lksjadf : w) z.pop_back();
	return z;
}

// Máximo pref de w que es suff de s[0..i)
vector<int> pref_end(string w, string s) {
	int len = -1;
	int n = int(s.size());

	vector<int> out(n+1);
	out[0] = 0;
	forn(i, 1, n+1) {
		while(len != -1 && s[len] != s[i-1]) len = tabla[len];
		len++;
		out[i] = len;
	}
	return out;
}

vector<int> join(string w, vector<int> suff) {
	int n = int(pref.size());
	vector<int> out(n+1);
	out[0] = 0;
}

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	long long int total = 0;
	int q, b;
	cin >> q >> b;
	forn(ksjdfha, 0, q) {
		string w;
		cin >> w;
		total += match(w, s);
	}
	cout << total << endl;
}
