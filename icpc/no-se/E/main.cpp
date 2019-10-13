#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;


int calc(string ns, vector<string> emo) {
	int n = int(ns.size());
	vector<pair<int, int>> evs;
	vector<bool> occ;
	for(string e : emo) {
		int k = int(e.size());
		forn(i, n-k+1) {
			if(e == ns.substr(i, k)) {
				evs.emplace_back(i, i+k);
				occ.push_back(false);
			}
		}
	}

	int total = 0;
	forn(j, n) {
		bool add = false;
		forn(i, evs.size()) {
			if(evs[i].second-1 ==j && !occ[i]) add = true;
		}
		if(add) {
			total++;
			forn(i, evs.size()) {
				if(evs[i].first <= j) occ[i] = true;
			}
		}
	}

	return total;
}

int main() {
	int n, m;
	while(cin >> n >> m && n+m != 0) {
		string tmp;
		getline(cin, tmp);
		vector<string> emo(n);
		for(string &s : emo) {
			getline(cin, s);
		}

		vector<string> ls(m);
		int total = 0;
		for(string &s : ls) {
			getline(cin, s);
			total += calc(s, emo);
		}

		cout << total << endl;
	}
}
