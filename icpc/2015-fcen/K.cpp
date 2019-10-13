#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;
typedef long long int ll;

int main() {
	int n, m;
	while(cin >> n >> m) {
		vector<ll> ns(n);
		forn(i, n) cin >> ns[i];
		
		struct Elem {
			ll s;
			ll c;
			bool operator<(Elem k) const {
				return make_pair(s, c) < make_pair(k.s, k.c);
			}
			Elem operator+(Elem k) {
				return Elem {s+k.s, c+k.c};
			}
		};
		vector<vector<Elem>> ms(n);
		forn(asldjfhkj, m) {
			ll l, s, c;
			cin >> l >> s >> c;
			--l;
			ms[l].push_back(Elem {s, c});
		}
		
		set<Elem> dom;
		dom.insert(Elem {0, 0});
		auto put = [&](Elem k) {
			auto l = dom.lower_bound(k);
			if(l != dom.end() && l->c <= k.c) return;
			while(true) {
				auto it = dom.upper_bound(k);
				// if(it != dom.end() && it->c <= k.c) goto mal;
				if(it == dom.begin()) break;
				it = prev(it);
				if(it->c >= k.c) dom.erase(it);
				else break;
			}
			dom.insert(k);
			/*for(Elem e : dom) {
				cerr << e.s << " " << e.c << ",";
			}*/
			// cerr << endl;
		};
		
		forn(i, n-1) ns[i+1] += ns[i];
		ns.insert(ns.begin(), 0ll);
		ll calc = 0;
		forn(i, n+1) {
			auto it = dom.lower_bound(Elem {ns[i], 0});
			// if(it != dom.end()) cerr << it->c << " -> " << it-> s << endl;
			if(it == dom.end()) {
				calc = -1;
				break;
			} else {
				calc = it->c;
				if(i != n) {
					for(Elem e : ms[i]) {
						e.c += it->c;
						e.s += ns[i];
						put(e);
					}
				}
			}
		}
		cout << calc << endl;
	}
}
