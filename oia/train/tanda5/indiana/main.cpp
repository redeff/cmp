#include <bits/stdc++.h>
using namespace std;

const int INF = 3333333;

vector<vector<pair<int, int>>> dp;
vector<vector<bool>> board;
int n;

enum Dir {
    VER, HOR,
};

int time(Dir from, Dir to, bool clockwise) {
    if(from == to) return 2;
    return ((from == VER) != clockwise) ? 3 : 1;
}

int get_len(int x, int y, Dir d) {
    {
        int this_one = ((d == VER) ? dp[x][y].first : dp[x][y].second);
        if(this_one != -1) return this_one;
    }

    if(x == n - 1 && y == n - 1) return time(d, HOR, board[x][y]);

    int ver = (y < n - 1) ? (get_len(x, y + 1, VER) + time(d, VER, board[x][y])) : INF;
    int hor = (x < n - 1) ? (get_len(x + 1, y, HOR) + time(d, HOR, board[x][y])) : INF;
    int ret = min(ver, hor);

    ((d == VER) ? dp[x][y].first : dp[x][y].second) = ret;
    return ret;
}

#define ifs cin
#define ofs cout

int main() {
    ifstream ifs("indiana.in");
    ofstream ofs("indiana.out");
    cin >> n;
    board = vector<vector<bool>>(n, vector<bool>(n));
    dp = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(n, {-1, -1}));

    for(int y = 0; y < n; ++y) {
        string s;
        cin >> s;
        for(int x = 0; x < n; ++x) {
            board[x][y] = s[x] == 'H';
        }
    }

    // for(int x = n - 1; x >= 0; --x) for(int y = n - 1; y >= 0; --y) get_len(x, y, VER), get_len(x, y, HOR);

    cout << get_len(0, 0, HOR) << endl;
}
