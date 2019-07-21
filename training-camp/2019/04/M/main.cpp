#include <bits/stdc++.h>
using namespace std;

#define ixin(x, ns) (lower_bound(ns.begin(), ns.end(), x) - ns.begin())

int main() {
	int t;
	int city = 0;
	while(cin >> t && t != 0) {
		++city;
		vector<pair<pair<int, int>, pair<int, int>>> ns(t+1);
		vector<int> xs;
		vector<int> ys;

		for(auto &p : ns) {
			cin >> p.first.first >> p.first.second >> p.second.first >> p.second.second;
			p.first.first *= 4;
			p.first.second *= 4;
			p.second.first *= 4;
			p.second.second *= 4;
			xs.push_back(p.first.first);
			xs.push_back(p.first.first + 1);
			xs.push_back(p.first.first - 1);
			xs.push_back(p.second.first);
			xs.push_back(p.second.first + 1);
			xs.push_back(p.second.first - 1);

			ys.push_back(p.first.second);
			ys.push_back(p.first.second + 1);
			ys.push_back(p.first.second - 1);
			ys.push_back(p.second.second);
			ys.push_back(p.second.second + 1);
			ys.push_back(p.second.second - 1);
		}

		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
		/*
		for(int i : xs) cout << i << " ";
		cout << endl;
		*/

		sort(ys.begin(), ys.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());
		/*
		for(int i : ys) cout << i << " ";
		cout << endl;
		*/

		int n = xs.size();
		int m = ys.size();

		int xb, yb, xe, ye;
		vector<vector<bool>> board(n, vector<bool>(m, false));
		int cont = 0;
		for(auto p: ns) {
			cont++;
			// cerr << p.first.second << endl;
			int x1 = ixin(p.first.first, xs);
			int x2 = ixin(p.second.first, xs);

			int y1 = ixin(p.first.second, ys);
			int y2 = ixin(p.second.second, ys);

			// cerr << "unDONE " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			if(cont != t+1) {
				for(int x = min(x1, x2); x <= max(x1, x2); ++x) {
					for(int y = min(y1, y2); y <= max(y1, y2); ++y) {
						board[x][y] = true;
					}
				}
			} else {
				// cerr << "DONE" << endl;
				xb = x1;
				yb = y1;
				xe = x2;
				ye = y2;
			}
		}

		vector<pair<int, int>> dirs = {
			{1, 0},
			{-1, 0},
			{0, 1},
			{0, -1},
		};

		auto inrange = [&](int x, int y) {
			return 0 <= x && x < n && 0 <= y && y < m;
		};

		/*
		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < m; ++y) {
				if(x == xb && y == yb) cerr << 'B';
				else if(x == xe && y == ye) cerr << 'E';
				else cerr << (board[x][y] ? '#' : ' ');
			}
			cerr << endl;
		}
		*/

		vector<vector<bool>> seen(n, vector<bool>(m, false));

		vector<pair<int, int>> bfs = {{xb, yb}};
		int dist = 0;
		while(true) {
			vector<pair<int, int>> nbfs;
			while(!bfs.empty()) {
				pair<int, int> to = bfs.back();
				bfs.pop_back();
				if(seen[to.first][to.second]) continue;
				seen[to.first][to.second] = true;
				if(to.first == xe && to.second == ye) {
					cout << "City " << city << "\n";
					cout << "Peter has to cross " << dist << " street";
					if(true || dist != 1) cout << "s";
					cout << "\n";
					// cout << dist << endl;
					goto out;
					// TODO
				}
				for(auto d : dirs) {
					pair<int, int> g = {to.first + d.first, to.second + d.second};
					if(inrange(g.first, g.second)) {
						if(board[g.first][g.second]) {
							nbfs.push_back(g);
						} else {
							bfs.push_back(g);
						}
					}
				}
			}

			swap(bfs, nbfs);
			dist++;
		}

out:;
	}
}
