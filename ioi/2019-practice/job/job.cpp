#include "job.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < int(n); ++i)

long long scheduling_cost(vector<int> dads, vector<int> costs, vector<int> times) {
	auto cmp = [&](int a, int b) -> bool {
		// La raíz es mayor que cualquier cosa, para que no la agarremos
		if(a == b) return false;
		if(-1 == dads[a] && -1 == dads[b]) return a < b;
		if(dads[a] == -1) return false;
		if(dads[b] == -1) return true;

		// Los (0, 0) son menores que cualquier cosa, pq sino no están bien ordenados
		// y no importa donde los ponemos
		bool za = costs[a] == 0 && times[a] == 0;
		bool zb = costs[b] == 0 && times[b] == 0;
		if(za && zb) return a < b;
		if(za) return true;
		if(zb) return false;
		
		// Los otros los ordeno por pendiente;
		// times[a] / costs[a] < times[b] / costs[b];
		int rhs = times[a]*costs[b];
		int lhs = times[b]*costs[a];
		if(rhs == lhs) return a < b;
		return rhs < lhs;
	};

	int n = int(dads.size());

	vector<vector<int>> graph(n);
	fore(i, 1, n) {
		graph[dads[i]].push_back(i);
	}

	set<int, decltype(cmp)> bag(cmp);
	fore(i, 0, n) bag.insert(i);

	long long total = 0;

	while(bag.size() > 1) {
		for(int i : bag) if(dads[i] != -1) {
			auto v = graph[dads[i]];
			for(int j : bag) if(j != dads[i]) {
				auto u = graph[j];
				assert(find(u.begin(), u.end(), i) == u.end());
			}
			assert(find(v.begin(), v.end(), i) != v.end());
			assert(dads[i] != i);
			assert(bag.count(dads[i]));
		}
		int ch = *bag.begin();
		bag.erase(bag.begin());

		int dad = dads[ch];
		assert(dad != ch);
		assert(dad != -1);
		assert(bag.count(dad));
		bag.erase(dad);

		total -= (long long)(times[ch]) * costs[dad];
		costs[dad] += costs[ch];
		times[dad] += times[ch];

		costs[ch] = costs[dad];
		times[ch] = times[dad];

		int small = graph[ch].size() < graph[dad].size() ? ch : dad;
		int big = dad + ch - small;

		for(int i : graph[small]) if(i != big) {
			graph[big].push_back(i);
			assert(dads[i] != -1);
			dads[i] = big;
		}
		graph[small] = {};

		if(big == ch) {
			if(dads[dad] != -1) {
				graph[dads[dad]].push_back(ch);
			}
			dads[ch] = dads[dad];
		}

		bag.insert(big);
	}

	int t = *bag.begin();
	total += (long long)(costs[t]) * times[t];
	return total;
}
