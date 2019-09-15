#include "job.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < int(n); ++i)

long long scheduling_cost(vector<int> dads, vector<int> costs, vector<int> times) {
	auto cmp = [&](int a, int b) -> bool {
		// La raíz es mayor que cualquier cosa, para que no la agarremos
		if(a == b) return false;
		if(a == 0) return false;
		if(b == 0) return true;

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
	/*
	fore(i, 1, n) {
		if(costs[dads[i]] == 0 && times[dads[i]] == 0) {
			dads[i] = dads[dads[i]];
		}
	}
	*/

	vector<vector<int>> graph(n);
	set<int, decltype(cmp)> bag(cmp);
	fore(i, 1, n) {
		graph[dads[i]].push_back(i);
		if(costs[i] != 0 || times[i] != 0) bag.insert(i);
	}

	int total = 0;

	int last = 0;
	while(!bag.empty()) {
		// for(int i : bag) assert(dads[i] != i);
		int t = *bag.begin();
		bag.erase(bag.begin());

		int d = dads[t];
		bool root = dads[d] == -1;
		last = d;
		// cerr << root << " RRRR " << d << endl;
		if(!root) bag.erase(d);
		// cerr << "SET ";
		// for(int i : bag) cerr << i << " ";
		// cerr << endl;

		/*
		cerr << d << " " << t << endl;
		cerr << "(" << costs[d] << "," << times[d] << ") ";
		cerr << "(" << costs[t] << "," << times[t] << ")" << endl;
		*/

		total -= times[t] * costs[d];
		costs[d] += costs[t];
		times[d] += times[t];
		
		costs[t] = costs[d];
		times[t] = times[d];

		bool sw = graph[t].size() < graph[d].size();
		assert(t != d);
		if(sw) {
			for(int i : graph[t]) {
				graph[d].push_back(i);
				assert(i != d);
				dads[i] = d;
			}
		} else {
			for(int i : graph[d]) if(t != i) {
				graph[t].push_back(i);
				// assert(i != t);
				dads[i] = t;
			}
			if(!root) graph[dads[d]].push_back(t);
		}

		/*
		for(int i : sw ? graph[t] : graph[d]) {
			(sw ? graph[d] : graph[t]).push_back(i);
			dads[i] = sw ? d : t;
		}
		*/

		// assert(d != dads[d]);
		dads[t] = dads[d];

		if(!root) bag.insert(sw ? d : t);
		// if(!root) bag.insert(sw ? t : d);
		// cerr << "SETE ";
		// for(int i : bag) cerr << i << " ";
		// cerr << endl;
	}

	total += times[last] * costs[last];
	return total;
}
