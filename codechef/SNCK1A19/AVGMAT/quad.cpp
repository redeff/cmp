#include <bits/stdc++.h>
using namespace std;
vector<int> calc(vector<vector<int>> &board, int n, int m) {
    vector<int> out(n + m - 1, 0);
    for(int x1 = 0; x1 < n; ++x1) {
        for(int x2 = 0; x2 < n; ++x2) {
            for(int y1 = 0; y1 < m; ++y1) {
                for(int y2 = 0; y2 < m; ++y2) {
                    int d = abs(x1 - x2) + abs(y1 - y2);
                    out[d] += board[x1][y1] * board[x2][y2];
                }
            }
        }
    }
    for(int &i: out) i /= 2;
    return out;
}

int main() {
    int t;
    cin >> t;
    for(int sdf = 0; sdf < t; ++sdf) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> board(n, vector<int>(m));
        for(int x = 0; x < n; ++x) {
            string s;
            cin >> s;
            for(int y = 0; y < m; ++y) {
                board[x][y] = s[y] - '0';
            }
        }

        auto d = calc(board, n, m);
        for(int i = 1; i < d.size(); ++i) cout << d[i] << " ";
        cout << endl;
    }
}
