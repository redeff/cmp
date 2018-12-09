#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for(int lala = 0; lala < t; ++lala) {
        int n, m;
        cin >> n >> m;

        vector<set<int>> graph(n*n);
        vector<vector<int>> board(n, vector<int>(n, -1));

        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            graph[a-1].insert(b-1);
            graph[b-1].insert(a-1);
        }

        for(int i = 0; i < n*n; ++i) if(graph[i].size() == 5) {
            board[0][0] = i;
            break;
        }

        for(int v : graph[board[0][0]]) {
            if(graph[v].size() == 7) {
                if(board[0][1] == -1) board[0][1] = v;
                else board[1][0] = v;
            }
        }
        
        for(int v : graph[board[0][0]]) {
            if(graph[board[1][0]].count(v) == 0 && v != board[1][0]) board[0][2] = v;
            if(graph[board[0][1]].count(v) == 0 && v != board[0][1]) board[2][0] = v;
        }

        for(int i = 3; i < n; ++i) {
            for(int v : graph[board[i-1][0]]) {
                if(graph[board[i-2][0]].count(v) != 0
                        && graph[v].size() < 8
                        && v != board[i-3][0]) {

                    board[i][0] = v;
                }
            }
        }

        for(auto& v : board) {
            for(int a : v) {
                cout << a << " ";
            }
            cout << endl;
        }
    }
}
