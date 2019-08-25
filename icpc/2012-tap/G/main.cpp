#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
ull base = 9813741;
ll INF = 33333333333333;

ull ex(int e) {
	static vector<ull> cache = {1ull};
	while(int(cache.size()) <= e) {
		cache.push_back(cache.back() * base);
	}
	return cache[e];
}

struct Str {
	ull hsh;
	int len;
};

/*
bool operator<(Str a, Str b) {
	return a.hsh < b.hsh;
}
*/

Str create(string s) {
	Str out;
	out.len = 0;
	out.hsh = 0;
	reverse(s.begin(), s.end());
	for(char c : s) {
		out.hsh *= base;
		out.hsh += c;
		out.len++;
	}
	return out;
}

Str operator+(Str a, Str b) {
	return Str {
		a.hsh + b.hsh * ex(a.len),
		a.len + b.len,
	};
}

struct Part {
	Str pre;
	Str post;
	ll value;
};

unordered_map<ull, ll> values;

ll value(Str s) {
	if(values.count(s.hsh)) return values[s.hsh];
	else return -INF;
}

Part parse(string s) {
	s.push_back('-');
	int n = int(s.size());

	Part out;
	out.value = 0;
	string curr = "";
	bool fst = true;
	for(int i = 0; i < n; ++i) {
		if(s[i] != '-') curr.push_back(s[i]);
		else {
			if(fst) {
				fst = false;
				out.pre = create(curr);
			} else if(i == n-1) {
				out.post = create(curr);
			} else {
				out.value += value(create(curr));
			}

			curr = "";
		}
	}

	return out;
}

ll join(Part a, Part b) {
	ll k = value(a.post + b.pre) + b.value;
	/*
	if(k > 0) assert(false);
	else {
		cerr << value(a.post + b.pre) << endl;
		cerr << b.value << endl;
	}
	*/
	return k;
}

int main() {
	int t, n;
	while(cin >> t >> n && t != -1) {
		vector<Part> ns = vector<Part>(n);
		values.clear();

		for(int i = 0; i < t; ++i) {
			string s;
			ll val;
			cin >> s >> val;
			Str st = create(s);
			values[st.hsh] = max(value(st), val);
		}

		for(Part &p : ns) {
			string s;
			ll i;
			cin >> s >> i;
			p = parse(s);
			p.value -= i;
			// cerr << p.value << endl;
		}

		vector<vector<ll>> mat(n, vector<ll>(n, -INF));
		for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
			mat[i][j] = join(ns[i], ns[j]);
			if(i == j) mat[i][j] = max(0ll, mat[i][j]);
			// cerr << i << " " << j << " - ";
			// cerr << mat[i][j] << endl;
		}

		auto run = [&]() {
			for(int k = 0; k < n; ++k) {
				for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
					mat[i][j] = max(mat[i][j], mat[i][k] + mat[k][j]);
				}
			}
		};

		run();
		auto mat2 = mat;
		run();

		auto dist = [&](int a, int b) {
			return mat[a][b]
				+ value(ns[b].post) + value(ns[a].pre) + ns[a].value;
		};

		ll best = 0;
		for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
			ll d = dist(i, j);
			if(d > -INF/2) {
				swap(mat, mat2);
				if(dist(i, j) != d) best = INF;
				else {
					best = max(best, d);
					// cerr << i << " " << j << " " << mat[i][j] << endl;
				}
				swap(mat, mat2);
			}
		}
		// cerr << mat[0][2] << endl;

		if(best == INF) cout << "*" << endl;
		else cout << best << endl;
		// cerr << value(create("hola")) << endl;
	}
}
