#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m && n != 0) {
        vector<int> ns(n);
        for(int &i : ns) cin >> i;

        vector<int> ms(m);
        for(int &i : ms) cin >> i;

        vector<vector<bool>> board(n, vector<bool>(m, 0));
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
            board[i][j] = (ns[i] > 0) && (ms[j] > 0);
            if(board[i][j]) {
                ns[i]--; ms[j]--;
            }
        }

        if(*max_element(ns.begin(), ns.end()) != 0) {
            cout << "Impossible" << endl;
        } else if(*max_element(ms.begin(), ms.end()) != 0) {
            cout << "Impossible" << endl;
        } else {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    cout << (board[i][j] ? 'Y' : 'N');
                }
                cout << endl;
            }
        }
    }
}
