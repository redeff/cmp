#include <bits/stdc++.h>
using namespace std;
#define dforn(i, n) for(int i = int(n-1); i >= 0; --i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define MAXN 1000000

struct st {
	int MAX;
	bool vec[4*MAXN];
	void init(int n) {
		MAX = 1 << (32-__builtin_clz(n));
		fill(vec, vec+2*MAX, false);
		// return vec+MAX;
	}
	// void updall() {dforn(i, MAX) vec[i] = vec[2*i] == vec[2*i+1]}
	void pset(int i, bool k) {
				i += MAX;
		vec[i] = vec[i] != k;

		while(i) { i/= 2; vec[i] = vec[2*i] != vec[2*i+1];}
	}
	bool pget(int i, int j) {return _pget(i+MAX, j+MAX);}
	bool _pget(int i, int j) {
		bool res = false;
		if(j-i <= 0) return res;
		if(i%2) res = res != vec[i++];
		res = res != _pget(i/2, j/2);
		if(j%2) res = res != vec[--j];
		return res;
	}
};

int main() {
	int p, v;
	while(cin >> p >> v) {
		vector<int> xs;
		vector<int> ys;
		vector<pair<int, int>> ps(p);
		forn(i, p) {
			int x, y;
			cin >> x >> y;
			xs.push_back(x);
			ys.push_back(y);
			ps[i].first = x;
			ps[i].second = y;
		}
		vector<pair<int, int>> vs(v);
		forn(i, v) {
			int x, y;
			cin >> x >> y;
			xs.push_back(x);
			ys.push_back(y);
			vs[i].first = x;
			vs[i].second = y;
		}
		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
		sort(ys.begin(), ys.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());
		forn(i, p) {
			ps[i].first = int(lower_bound(xs.begin(), xs.end(), ps[i].first) - xs.begin());
			ps[i].second = int(lower_bound(ys.begin(), ys.end(), ps[i].second) - ys.begin());
		}
		forn(i, v) {
			vs[i].first = int(lower_bound(xs.begin(), xs.end(), vs[i].first) - xs.begin());
			vs[i].second = int(lower_bound(ys.begin(), ys.end(), vs[i].second) - ys.begin());
		}
		
		st ranges;
		ranges.init(p+v);
		
		struct Event {
			int x; int y;
			int type;
			int index;
			bool operator<(Event k) const {
				if(x != k.x) return x < k.x;
				else return type < k.type;
			}
		};
		vector<Event> evs;
		forn(i, p) evs.push_back(Event {ps[i].first, ps[i].second, 1, i+1});
		forn(i, v) evs.push_back(Event {vs[i].first, vs[i].second, 0, 0});
		sort(evs.begin(), evs.end());
		long long int total = 0;
		for(Event e : evs) {
			if(e.type == 0) {
				// cerr << e.y << " ";
				ranges.pset(e.y, true);
			} else {
				// cerr << e.y << "?" << ranges.pget(0, e.y) << " "; 
				if(!ranges.pget(0, e.y)) total += e.index;
			}
		}
		// cerr << endl;
		cout << total << endl;
	}
}
