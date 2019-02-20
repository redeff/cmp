#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int t;
	cin >> t;
	for(int la = 0; la < t; ++la) {
		int n;
		cin >> n;

		vector<vector<int>> board(n, vector<int>(n));
		int curr = 1;
		int row = 0;
		int x = 0;
		int y = 0;
		while(row < 2 * n + 10) {
			if(x < n && x >= 0 && y < n && y >= 0) {
				board[x][y] = curr;
				curr++;
			} else if(x < 0) {
				y = 0;
				row++;
				x = row;
				x++;
				y--;
			}

			x--;
			y++;

		}

		for(int y = 0; y < n; ++y) {
			for(int x = 0; x < n; ++x) {
				cout << board[x][y] << " ";
			}
			cout << endl;
		}
	}
}
