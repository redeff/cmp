#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define dforn(i, n) for(int i = n-1; i >= 0; --i)
using namespace std;

// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3805

vector<int> prv(vector<int> &ns) {
	int n = int(ns.size());
	vector<int> out(n);
	forn(i, n) {
		int k = i-1;
		while(k != -1 && ns[k] >= ns[i]) k = out[k];
		out[i] = k;
	}
	return out;
}

void rev(vector<int> &ns) {
	int n = int(ns.size());
	reverse(ns.begin(), ns.end());
	for(int &i : ns) i = n-i-1;
}


pair<vector<int>, vector<int>> bwt(string s) {
	int n = int(s.size());
	vector<int> p(n);
	vector<int> r(n);
	int bc[256];
	memset(bc, 0, sizeof(bc));
	forn(i, n) ++bc[(unsigned char)(s[i])];
	forn(i, 255) bc[i+1]+=bc[i];
	forn(i, n) r[--bc[(unsigned char)(s[i])]]=i;
	forn(i, n) p[i]=bc[(unsigned char)(s[i])];
	
	int lnb,nb = 1;
	for(int t = 1; t < n; t*=2) {
		auto sacmp = [&](int a, int b) {
			return p[(a+t) %n] < p[(b+t) %n];
		};
		lnb = nb; nb = 0;
		for(int i = 0, j = 1; i < n; i = j++) {
			while(j < n && p[r[j]] == p[r[i]]) ++j;
			if (j-i > 1) {
				sort(r.begin()+i, r.begin()+j, sacmp);
				int pk, opk = p[(r[i]+t) %n];
				int q = i, v = i;
				for(; i < j; i++) {
					if (((pk = p[(r[i]+t) %n]) != opk) && !(q <= opk && pk < j)) {
						opk = pk;
						v = i;
					}
					p[r[i]] = v;
				}
			}
			nb++;
		}
		if (lnb == nb) break;
	}
	return {r, p};
}

tuple<vector<int>, vector<int>, vector<int>> lcp(string s) { /* h could be over r */
	int n = int(s.size());
	vector<int> h(n);
	vector<int> r, p;
	tie(r,p) = bwt(s + "$");
	int q = 0, j;
	forn(i,n) if (p[i]) {
		j = r[p[i]-1];
		while(q < n && s[(i+q) %n] == s[(j+q) %n]) ++q;
		h[p[i]-1] = q;
		if (q > 0) --q;
	}
	forn(i, n) h[i] = min(h[i], min(n-r[i], n-r[i+1]));
	return {r,p,h};
}

typedef long long unsigned int bit;
const int lvl = 21;
bit vec[lvl][1<<lvl];
bit uni(int i, int j) {
	int p = 31-__builtin_clz(j-i);
	return vec[p][i] | vec[p][j-(1<<p)];
}

void init(int n) {
	// int n = int(ns.size());
	// forn(i, n) vec[0][i] = ns[i];
	int mp = 31-__builtin_clz(n);
	forn(p, mp) forn(x, n-(1<<p))
		vec[p+1][x] = vec[p][x] | vec[p][x+(1<<p)];
}

pair<vector<int>, vector<int>> lr(vector<int> ns) {
	auto left = prv(ns);
	reverse(ns.begin(), ns.end());
	auto right = prv(ns);
	rev(right);
	return {left, right};
}

int main() {
	int n;
	while(cin >> n && n != 0) {
		vector<string> ns(n);
		for(string &s : ns) cin >> s;
		// cerr << "AAAAA" << endl;
		string total;
		vector<bit> index;
		vector<int> len;
		forn(i, n) {
			forn(j, ns[i].size()) {
				total.push_back(ns[i][j]);
				index.push_back(1ull << bit(i));
				len.push_back(int(ns[i].size())-j);
			}
			len.push_back(-1);
			total.push_back('a'-1-i);
			index.push_back(0);
		}
		// cerr << total << endl;
		vector<int> ord, inv, lc;
		tie(ord, inv, lc) = lcp(total);
		len.push_back(-1);
		index.push_back(0);
		int m = int(total.size())+1;
		// assert(index.size() == m);
		forn(i, m) vec[0][i] = index[ord[i]];
		vec[0][m] = 0;
		vec[0][m+1] = 0;
		init(m+2);
		vector<int> left, right;
		tie(left, right) = lr(lc);
		forn(i, m) assert(inv[ord[i]] == i);
		/*
		forn(i, m) {
			cout << i << ": \t";
			if(i < m-1) cout << lc[i];
			cout << " \t";
			if(i < m-1) cout << left[i];
			cout << " \t"; 
			if(i < m-1) cout << right[i];
			cout << " \t";
			cout << len[ord[i]];
			cout << " \t";
			cout << index[ord[i]];
			cout << " \t";
			cout << total.substr(ord[i]) << endl;
		}
		cout << endl;
		*/
		unordered_set<bit> poss;

		forn(i, m-1) {
			if(lc[i] == 0) continue;
			int a = left[i]+1;
			int b = right[i]+1;
			if(uni(a,b) == 1) {
				// cerr << i << " " << a << " " << b << endl;
				// cerr << ord[a] << " " << ord[b-1] << endl;
				// cerr << uni(a,b) << endl;
			}
			poss.insert(uni(a, b));
		}
		forn(i, m) {
			if(len[ord[i]] <= 0) continue;
			if(i != 0 && len[ord[i]] <= lc[i-1]) continue;
			if(i != m-1 && len[ord[i]] <= lc[i]) continue;
			// cerr << len[i] << endl;
			/*
			if(index[ord[i]] == 1) {
				cerr << i << endl;
			}*/
			poss.insert(index[ord[i]]);
		}
		// for(bit k : poss) cerr << bitset<10>(k) << endl;
		poss.erase(0);
		cout << poss.size() << endl;
	}
}
