#include <bits/stdc++.h>
using namespace std;

bool has_perfect_matching(vector<vector<int>> &left, vector<vector<int>> &right) {
    vector<int> left_match(left.size(), -1);
    vector<int> right_match(right.size(), -1);

    bool emp = true;
    while(emp) {
        vector<int> left_visited(left.size(), false);
        vector<int> right_visited(right.size(), false);

        function<bool(bool, int)> dfs = [&](bool l, int index) {
            if(l && left_visited[index]) return false;
            if(!l && right_visited[index]) return false;

            if(l) left_visited[index] = true;
            else right_visited[index] = true;

            auto match = l ? left_match[index] : right_match[index];
            auto &graph = l ? left[index] : right[index];

            if(!l && match == -1) return true;

            for(auto ch: graph) if(l == (ch != match)) {
                bool v = dfs(!l, ch);
                if(v && l) {
                    left_match[index] = ch;
                    right_match[ch] = index;
                }

                if(v) return true;
            }

            return false;

        };

        emp = false;
        for(int i = 0; i < left.size(); ++i) if(left_match[i] == -1) {
            if(dfs(true, i)) {
                emp = true;
                break;
            }
        }
    }

    for(int i : left_match) if(i == -1) return false;
    for(int i : right_match) if(i == -1) return false;

    return true;
}

vector<pair<int, int>> dirs = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

int main() {
    int n, m;
    while(cin >> n) {
        cin >> m;

        vector<vector<int>> indices(n, vector<int>(m, 0));
        vector<string> board(n);
        for(int i = 0; i < n; ++i) cin >> board[i];

        int white = 0;
        int black = 0;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) if(board[i][j] != 'X'){
            if((i + j) % 2 == 0) {
                indices[i][j] = white;
                white++;
            } else {
                indices[i][j] = black;
                black++;
            }
        }

        vector<vector<int>> left(white);
        vector<vector<int>> right(black);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) if(board[i][j] != 'X') {
            for(auto d : dirs) {
                int x = i + d.first;
                int y = j + d.second;
                if(x >= 0 && x < n && y >= 0 && y < m && board[x][y] != 'X') {
                    (((i + j) % 2 == 0) ? left : right)[indices[i][j]].push_back(indices[x][y]);
                }
            }
        }

        if(has_perfect_matching(left, right)) {
            cout << 2 << endl;
        } else cout << 1 << endl;
    }
}
