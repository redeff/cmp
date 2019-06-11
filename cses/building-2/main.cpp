#include <bits/stdc++.h>
using namespace std;

#define forn(x, n) for(int x = 0; x < (int)(n); ++x)
#define rfor(x, n) for(int x = int(n)-1; x >= 0; --x)

int main() {

	// Input
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
		// We will count all rectangles with bases lying on row x and
		// extending upwards (towards negative x)

		// (last[y], y) is the lowest tree in column y
		// (with x coordinate leq to x)
		forn(y, m) {
			if(board[x][y]) last[y] = x;
		}

		// For each tree, left[y] is the column of the first tree to the
		// left of tree (y, last[y]) with a greater x coordinate (but leq to
		// x)
		vector<int> left(m);
		left[0] = -1;
		forn(y, m) {
			int k = y-1;
			while(k != -1 && last[k] <= last[y])
				k = left[k];
			left[y] = k;
		}

		// The same but to the right, and its >= not >, the asymmetry comes
		// from the definition of "representatives" below
		vector<int> right(m);
		right[m-1] = m;
		rfor(y, m) {
			int k = y+1;
			while(k != m && last[k] < last[y])
				k = right[k];
			right[y] = k;
		}


		// The "representative tree" of each rectangle with a base lying on
		// row x is defined as the tree with the greatest x coordinate (but
		// leq to x) that is within the rightmost and leftmost columns of the
		// rectangle, in case of ties, we take the rightmost one
		forn(y, m) {

			// We will consider every rectangle with base in row x and
			// representative tree (left[y], y)

			// the distance between the column y and the rightmost column of
			// our rectangle is at most a, likewise the distance between the
			// column y and the leftmost column of the rectangle is at most
			// b
			int a = right[y] - y - 1;
			int b = y - left[y] - 1;

			// The height of the rectangle is between 0 and h
			int h = x - last[y];

			// The numbers a, b and h are bounds on parameters that are in
			// bijection with all the rectangles reprented by tree (left[y],
			// y). That is, for any 0 < a' <= a, 0 < b' <= b; and 0 < h' <=
			// h, there exists exactly one tree with leftmost column y - b',
			// rightmost column y + a', and with a height h' that is
			// represented by (left[y], y) and has a base in row x
			//
			// So we would like to do:
			// for a' in 1..a:
			//   for b' in 1..b:
			//     for h' in 1..h:
			//       // The width of the rectangle is a' + b' + 1 and
			//       // its height is h
			//       res[h-1][a'+ b'] += 1
			//
			// But that takes too long, so we take the triple derivative of
			// the array res, once en the vertical coordinate and twice on
			// the horizontal coordinate, so that res only canges in three
			// places:

			if(h > 0) {
				res[h-1][a + b]++;
				if(a-1 >= 0) res[h-1][a-1]--;
				if(b-1 >= 0) res[h-1][b-1]--;
			}
		}
	}

	// Then we integrate res to get back to the original representation

	// First in the vertical direction
	rfor(x, n) if(x != 0) {
		forn(y, m) {
			res[x-1][y] += res[x][y];
		}
	}

	// And then twice in the horizontal direction
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

	// Output
	forn(x, n) {
		forn(y, m) {
			cout << res[x][y] << " ";
		}
		cout << "\n";
	}
}
