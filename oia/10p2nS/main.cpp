#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll INF = 333333333;
struct Client {
	ll x;
	ll y;
	ll t;
	ll w;
	int p;
	ll dist(Client o) {
		return abs(x - o.x) + abs(y - o.y);
	}
	ll b;
};

int main() {
#ifndef LOLOLOL
#define cin tata
#define cout tutu
	ifstream cin("negocios.in");
	ofstream cout("negocios.out");
#endif

	int n;
	cin >> n;
	vector<Client> ns(n);
	for(Client &i : ns) cin >> i.x >> i.y >> i.t >> i.w;

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int a, int b) {return ns[a].t < ns[b].t;});

	Client me;
	me.x = 0;
	me.y = 0;

	for(int i : ord) {
		ns[i].p = -2;
		ns[i].b = -INF;
		if(ns[i].dist(me) <= ns[i].t) {
			ns[i].p = -1;
			ns[i].b = 0;
		}
		for(int j : ord) if(j == i) break; else {
			if(ns[i].dist(ns[j]) <= ns[i].t - ns[j].t - 3) {
				if(ns[i].b < ns[j].b) {
					ns[i].b = ns[j].b;
					ns[i].p = j;
				}
			}
		}
		ns[i].b += ns[i].w;
	}
	
	int winner = *max_element(ord.begin(), ord.end(), [&](int a, int b) {return ns[a].b < ns[b].b;});
	if(ns[winner].b < 0) {
		cout << "0\n \n";
		return 0;
	}
	cout << ns[winner].b << endl;

	vector<int> pat;
	while(winner >= 0) {
		pat.push_back(winner);
		winner = ns[winner].p;
	}
	reverse(pat.begin(), pat.end());
	for(int i : pat) cout << i+1 << " ";
	cout << endl;
}
