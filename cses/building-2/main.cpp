#include <bits/stdc++.h>
using namespace std;

#define forn(x, n) for(int x = 0; x < (int)(n); ++x)
#define rfor(x, n) for(int x = int(n)-1; x >= 0; --x)

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> board(n, vector<bool>(m));
	forn(x, n) {
		string s;
		cin >> s;
		forn(y, m) board[x][y] = s[y] == '*';
	}

	vector<vector<int>> res(n, vector<int>(m, 0));
	vector<int> last(m, -1);
	forn(x, n) {
		forn(y, m) {
			if(board[x][y]) last[y] = x;
		}

		vector<int> left(m);
		left[0] = -1;
		forn(y, m) {
			int k = y-1;
			while(k != -1 && last[k] <= last[y])
				k = left[k];
			left[y] = k;
		}

		vector<int> right(m);
		right[m-1] = m;
		rfor(y, m) {
			int k = y+1;
			// cerr << k << endl;
			while(k != m && last[k] < last[y])
				k = right[k];
			right[y] = k;
		}

		forn(y, m) {
			// if(right[y] != m && last[right[y]] == last[y]) continue;
			int w = right[y] - left[y] - 1;
			int a = right[y] - y;
			int b = y - left[y];
			int h = x - last[y];
			if(h > 0) {
				// Derivamos dos veces en la dirección "y", y una vex en la
				// dirección "x"
				res[h-1][w-1]++;
				if(a-2 >= 0) res[h-1][a-2]--;
				if(b-2 >= 0) res[h-1][b-2]--;
				// if(d-2 >= 0) res[h-1][d-2]--;
			}
		}
	}

	// Acá integramos
	
	// Una vex en "x"
	rfor(x, n) if(x != 0) {
		forn(y, m) {
			res[x-1][y] += res[x][y];
		}
	}


	// Dos veces en "y"
	forn(x, n) {
		rfor(y, m) if(y != 0) {
			res[x][y-1] += res[x][y];
		}
	}


	forn(x, n) {
		rfor(y, m) if(y != 0) {
			res[x][y-1] += res[x][y];
		}
	}

	forn(x, n) {
		forn(y, m) {
			cout << res[x][y] << " ";
		}
		cout << "\n";
	}
}
