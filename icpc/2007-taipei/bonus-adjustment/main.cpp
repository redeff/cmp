#include <bits/stdc++.h>
using namespace std;
int n, m;

vector<vector<bool>> flow(vector<int> &rows, vector<int> cols, vector<vector<bool>> frac) {
	vector<vector<bool>> is(n, vector<bool>(m, false));

	// v
	for(int t = 0; t < n*m; ++t) {
		vector<pair<int, int>> aug;
		// vector<vector<bool>> seen(n, vector<bool>(m, false));
		auto seen = frac;
		function<bool(int, int)> sear = [&](int a, int b) {
			if(seen[a][b]) return false;
			seen[a][b] = true;
			if(cols[b] > 0) {
				// cerr << "YA" << endl;
				// cerr << a << " " << b << " = " << frac[a][b] << endl;
				aug.emplace_back(a, b);
				return true;
			} else {
				// cerr << "NP" << endl;
			}
			for(int x = 0; x < n; ++x) if((is[a][b] != is[x][b]) && !seen[x][b]) {
				seen[x][b] = true;
				for(int y = 0; y < m; ++y) if((is[x][y] != is[x][b]) && !seen[x][y]){
					if(sear(x, y)) {
						aug.emplace_back(x, b);
						aug.emplace_back(a, b);
						return true;
					}
				}
			}

			return false;
		};
		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < m; ++y) if(rows[x] > 0 && !is[x][y] && !frac[x][y]) {
				if(sear(x, y)) goto out;
			}
		}
		continue;
out:;
		for(auto p : aug) {
			if(is[p.first][p.second]) {
				rows[p.first]++;
				cols[p.second]++;
			} else {
				rows[p.first]--;
				cols[p.second]--;
			}
			// cerr << "A" << endl;
			is[p.first][p.second] = !is[p.first][p.second];
		}
	}

	return is;
}

int main() {
	int test;
	cin >> test;
	while (test --> 0) {
		cin >> n >> m;
		vector<double> rowsf(n, 0.0);
		vector<double> colsf(m, 0.0);
		vector<vector<double>> mat(n, vector<double>(m));
		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			cin >> mat[x][y];
			rowsf[x] += mat[x][y];
			colsf[y] += mat[x][y];
		}

		vector<int> rows(n);
		for(int x = 0; x < n; ++x) rows[x] = (int) (round(rowsf[x]) + 0.0001);
		vector<int> cols(m);
		for(int y = 0; y < m; ++y) cols[y] = (int) (round(colsf[y]) + 0.0001);

		vector<vector<bool>> frac(n, vector<bool>(m));

		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			frac[x][y] = ((double) (int) (mat[x][y] + 0.0001)) == mat[x][y];
			// cout << mat[x][y] << " -> " << frac[x][y] << endl;
			rows[x] -= (int) (mat[x][y] + 0.0001);
			cols[y] -= (int) (mat[x][y] + 0.0001);
		}

		// vector<vector<bool>> is(n, vector<bool>(m, false));
		auto is = flow(rows, cols, frac);
		/*
		for(int x = 0; x < n; ++x) for(int y = 0; y < m; ++y) {
			if(rows[x] > 0 && cols[y] > 0 && frac[x][y]) {
				rows[x]--;
				cols[y]--;
				is[x][y] = true;
			}
		}
		*/

		for(int x = 0; x < n; ++x) if(rows[x] != 0) {
			cerr << rows[x] << endl;
			cout << "no" << endl;
			goto nxt;
		}

		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < m; ++y) {
				cout << ((int) (mat[x][y] + 0.0001)) + is[x][y];
				// cout << is[x][y];
				if(y != m-1) cout << " ";
			}
			// if(x != n-1) cout << endl;
			cout << endl;
		}
nxt:;
	}
}
