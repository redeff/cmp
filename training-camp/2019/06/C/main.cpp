#include <bits/stdc++.h>
#define sun(ns) {sort(ns.begin(), ns.end()); ns.erase(unique(ns.begin(), ns.end()), ns.end());}
#define idx(i, ns) (lower_bound(ns.begin(), ns.end(), i) - ns.begin())
using namespace std;

int main() {
#define cin kjsdhfsjfh
#define cout lakjsdlajkd
	ifstream cin("control.in");
	ofstream cout("control.out");
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mat(n, vector<int>(m));
	vector<int> col;
	for(auto &v : mat) for(auto &i : v) {
		cin >> i;
		col.push_back(i);
	}

	sun(col);

	vector<int> imp;
	vector<pair<int, int>> edges;
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(mat[0][j] != mat[i][j]) {
				imp.push_back(mat[0][j]);
				imp.push_back(mat[i][j]);
				edges.push_back({mat[0][j], mat[i][j]});
				goto done;
			}
		}
		cout << "No\n";
		return 0;
done:;
	}

	sun(imp);
	// vector<vector<bool>> graph(imp.size(), vector<int>(imp.size(), false));
	vector<unordered_set<int>> graph(imp.size());
	vector<vector<int>> cols(imp.size());
	vector<int> avail;
	for(int i : imp) {
		int a = idx(i, imp);
		cols[a].push_back(i);
		avail.push_back(a);
	}

	for(pair<int, int> e : edges) {
		int a = idx(e.first, imp);
		int b = idx(e.second, imp);
		graph[a].insert(b);
		graph[b].insert(a);
	}


	random_shuffle(avail.begin(), avail.end());
	while(avail.size() > 48) {
		for(int i : avail) for(int j : avail) if(i != j) {
			if(!graph[i].count(j)) {
				avail.erase(find(avail.begin(), avail.end(), j));
				for(int k : graph[j]) {
					graph[i].insert(k);
					graph[k].insert(i);
				}
				for(int k : cols[j]) {
					cols[i].push_back(k);
				}
				cols[j] = {};
				goto nxt;
			}
		}
nxt:;
	}

	vector<int> res(col.size(), -1);
	for(int i = 0; i < cols.size(); ++i) {
		for(int k : cols[i]) {
			res[idx(k, col)] = i;
		}
	}

	auto v = res;
	sun(v);
	cout << "Yes" << endl;
	for(int i = 0; i < col.size(); ++i) {
		cout << col[i] << " -> " << idx(res[i], v) << "\n";
	}
}
