#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = int(z); i < int(n); ++i)
using namespace std;

vector<vector<int>> lcp_algo(string s) {
	int n = int(s.size());

	vector<vector<int>> out(n+1, vector<int>(n+1));
	forn(i, 0, n+1) out[n][i] = 0;
	forn(i, 0, n+1) out[i][n] = 0;

	forn(ri, 0, n) forn(rj, 0, n) {
		int i = n-ri-1;
		int j = n-rj-1;
		if(s[i] == s[j]) out[i][j] = out[i+1][j+1] + 1;
		else out[i][j] = 0;
	}

	return out;
}

// Devuelve el máximo subarray de la string w que interesa y es
// prefijo de s[i..]
vector<pair<int, int>> subarrays(
		string &s,
		string &w,
		vector<vector<int>> &lcp,
		vector<vector<int>> &hints) {

	int len = 0;
	int index = 0;

	int n = int(s.size());
	vector<pair<int, int>> res(n);
	forn(i, 0, n) {
		for(int h : hints[i]) {
			// cerr << index << " "  << h << endl;
			// index = h;
			while(i+len < n
					&& lcp[index][h] >= len
					&& s[i+len] == w[h+len]) {
				// assert(h + len < w.size());
				index = h;
				len++;
			}
		}
		res[i].first = index;
		// cerr << len << ";";
		res[i].second = len;
		index++;
		--len;
		if(len < 0) {
			len = 0;
			index = 0; // whatever
		}
	}
	// cerr << endl;
	res.push_back({0,0});
	return res;
}

vector<int> step(
		string &s,
		string &w,
		vector<vector<int>> &lcp,
		vector<int> pref){

	int n = int(s.size());
	vector<vector<int>> hints(n+1);
	forn(i, 0, n+1) hints[i+pref[i]].push_back(pref[i]);
	auto sub = subarrays(s, w, lcp, hints);

	vector<int> res(n+1);
	forn(i, 0, n) {
		auto p = sub[i+pref[i]];
		res[i] = pref[i] + min(lcp[p.first][pref[i]], p.second);
		assert(res[i] <= int(w.size()));
	}
	res[n] = 0;
	return res;
}

vector<int> add_err(vector<int> &pref, int bound) {
	vector<int> out(pref.size());
	forn(i, 0, pref.size()) {
		out[i] = pref[i];
		assert(i+pref[i] < int(pref.size()));
		assert(pref[i] <= bound);
		if(out[i] != bound && i+out[i] != int(pref.size())-1) out[i]++;
	}
	return out;
}

int calc(string w, string s, int errors) {
	auto lcp = lcp_algo(w);
	int n = int(s.size());
	vector<int> curr(n+1, 0);
	curr = step(s, w, lcp, curr);
	/*
	for(char c : s) cerr << c << " ";
	cerr << endl;
	for(int i : curr) cerr << i << ":";
	cerr << endl;
	*/
	forn(sjahflkjsf, 0, errors) {
		curr = add_err(curr, int(w.size()));
		curr = step(s, w, lcp, curr);
	}

	int total = 0;
	for(int i : curr) if(i == int(w.size())) total++;
	// cerr << total << endl;
	return total;
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
		total += calc(w, s, 1);
	}
	cout << total << endl;
}
