#include <bits/stdc++.h>
using namespace std;

struct Client {
	int bound[2];
	Client* dp;
	Client* nxt[2];
	int best;
	int whose;
	int index;
};

int main() {
#ifndef LOLOLOL
#define cin ajdsfhksadf
#define cout skjdfhaksh
	ifstream cin("mercachifle.in");
	ofstream cout("mercachifle.out");
#endif
	vector<Client> ns[2];
	for(int d = 0; d < 2; ++d) {
		int n;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			ns[d].emplace_back();
			cin >> ns[d].back().bound[0] >> ns[d].back().bound[1];
			ns[d].back().whose = d;
			ns[d].back().index = i;
			ns[d].back().bound[1]++;
			ns[d].back().nxt[0] = nullptr;
			ns[d].back().nxt[1] = nullptr;
			ns[d].back().dp = nullptr;
		}
	}

	vector<Client*> ord[2][2];
	for(int d = 0; d < 2; ++d) for(int f = 0; f < 2; ++f) {
		for(int i = 0; i < ns[d].size(); ++i) ord[f][d].push_back(&ns[d][i]);
		sort(ord[f][d].begin(), ord[f][d].end(), [&](Client *a, Client *b) {
			return a->bound[f] < b->bound[f];
		});
	}

	for(int d = 0; d < 2; ++d) {
		int curr = 0;
		for(Client *c : ord[1][d]) {
			while(
				curr < ord[1][1-d].size()
				&& ord[1][1-d][curr]->bound[0] < c->bound[1]
			) curr++;
			c->nxt[0] = curr < ord[1][1-d].size() ? ord[1][1-d][curr] : nullptr;
		}

		for(int i = 0; i < ord[0][d].size(); ++i) {
			ord[0][d][i]->nxt[1] =
				i+1 < ord[0][d].size() ? ord[0][d][i+1] : nullptr;
		}
	}

	vector<Client*> all;
	for(int d = 0; d < 2; ++d) for(int i = 0; i < ns[d].size(); ++i) all.push_back(&ns[d][i]);

	sort(all.begin(), all.end(), [&](Client *a, Client *b) {
		return a->bound[0] > b->bound[0];
	});

	for(Client *c : all) {
		c->best = 0;
		for(int d = 0; d < 2; ++d) {
			if(c->nxt[d] != nullptr && c->nxt[d]->best > c->best) {
				c->best = c->nxt[d]->best;
				c->dp = c->nxt[d];
			}
		}
		c->best++;
	}
	
	Client *c = *max_element(all.begin(), all.end(), [&](Client *a, Client *b) {
			return a->best < b->best;
	});

	vector<int> res[2];
	while(c != nullptr) {
		res[c->whose].push_back(c->index + 1);
		c = c->dp;
	}

	cout << res[0].size() + res[1].size() << endl;
	for(int d = 0; d < 2; ++d) {
		for(int i : res[d]) cout << i << " ";
		cout << endl;
	}
}
