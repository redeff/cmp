#include<bits/stdc++.h>
using namespace std;

int main() {

    cout << 1 << endl;
    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> board[i][j];
        }
    }

    int total = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int x = 0; x < n; ++x) {
                for(int y = 0; y < n; ++y) {
                    if(board[i][j] < board[x][y]) {
                        if(abs(x - i) + abs(y - j) < 3) {
                            total++;
                        }
                    }
                }
            }
        }
    }

    cout << n << " " << total << endl;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int x = 0; x < n; ++x) {
                for(int y = 0; y < n; ++y) {
                    if(board[i][j] < board[x][y]) {
                        if(abs(x - i) + abs(y - j) < 3) {
                            cout << board[i][j] << " " << board[x][y] << endl;
                        }
                    }
                }
            }
        }
    }
}
