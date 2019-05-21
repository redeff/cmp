#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll BOUND = 100000;
int ft[BOUND];

// Devuelve A[a]
int ft_get (int a) {
	a+=10;
	int v = 0;
	for (int x = a; x; x -= x & -x)
		v += ft[x];
	return v;
}

// Realiza A[a..BOUND] += v
void ft_set (int a, int v){
	a+=10;
	for (int x = a; x < BOUND; x += x & -x)
		ft[x] += v;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) cin >> i;

	int q;
	cin >> q;

	struct Query {
		int a;
		int b;
		int i;
		int res = -1;
	};

	vector<Query> qs(q);
	for(int i = 0; i < int(qs.size()); ++i) {
		cin >> qs[i].a >> qs[i].b;
		qs[i].a--;
		qs[i].b--;
		qs[i].i = i;
	}

	// Sorteo las queries por el final del rango
	sort(qs.begin(), qs.end(), [&](Query a, Query b) {return a.b < b.b;});

	int index = 0;

	// Lasts tiene la última aparición de cada numero en ns
	vector<int> lasts(2000000, -1);

	// Voy agregando de a uno por los elementos de ns desde la 0 hasta i
	// mantentiendo un ft que me dice, para cada indice j, cuantos distintos hay
	// desde j hasta i (inclusive)
	for(int i = 0; i < n; ++i) {
		int nxt = ns[i];

		// Con estas dos llamadas, le sumo uno a todos los del rango
		// (lasts[nxt], i], que son los que tienen un nuevo distinto gracias
		// al número de ns que agregué
		ft_set(lasts[nxt]+1, 1);
		ft_set(i+1, -1);

		lasts[nxt] = i;

		while(index < int(qs.size()) && qs[index].b == i) {
			qs[index].res = ft_get(qs[index].a);
			index++;
		}
	}

	sort(qs.begin(), qs.end(), [&](Query a, Query b) {return a.i < b.i;});
	for(Query t : qs) cout << t.res << "\n";
}
