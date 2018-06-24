#include <bits/stdc++.h>
using namespace std;

struct Rect {
	int x1;
	int x2;
	int y1;
	int y2;
};

enum Poss {
	YES,
	NO,
	IDK
};

int main() {
    int testcase = 0;
    while(true) {
        testcase++;
        int m, n, w;
        cin >> m >> n >> w;
        if(m==0) break;
        vector<int> xs;
        set<int> diffxs {0, n};
        vector<int> ys;
        set<int> diffys {0, m};

        vector<Rect> rects;
        for(int i = 0; i < w; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rects.push_back(Rect{.x1=x1, .x2=x2, .y1=y1, .y2=y2});
            diffys.insert(y1);
            diffys.insert(y2+1);
            diffxs.insert(x1);
            diffxs.insert(x2+1);
        }
        
        for(auto it = diffys.begin(); it != diffys.end(); ++it) {
            ys.push_back(*it);
        }

        for(auto it = diffxs.begin(); it != diffxs.end(); ++it) {
            xs.push_back(*it);
        }

        vector<vector<Poss>> board(xs.size() - 1, vector<Poss>(ys.size() - 1, IDK));
        board.back().back() = YES;
        for(Rect r : rects) {
            int xl = lower_bound(xs.begin(), xs.end(), r.x1) - xs.begin();
            int xh = lower_bound(xs.begin(), xs.end(), r.x2+1) - xs.begin();
            int yl = lower_bound(ys.begin(), ys.end(), r.y1) - ys.begin();
            int yh = lower_bound(ys.begin(), ys.end(), r.y2+1) - ys.begin();
            for(int i = xl; i < xh; ++i) for(int j = yl; j < yh; ++j) {
                board[i][j] = NO;
            }
        }

#ifndef ONLINE_JUDGE
        for(int x = 0; x < xs.size() - 1; ++x) {
            for(int y = 0; y < ys.size() - 1; ++y) {
                cout << (board[x][y] == NO ? "#" : ".");
            }
            cout << endl;
        }
#endif

        long long int total = 0;

        for(int i = xs.size() - 2; i >= 0; --i) {
            for(int j = ys.size() - 2; j >= 0; --j) {
                if(board[i][j] != IDK) continue;
                if(j < ys.size()-2 && board[i][j+1] == YES) board[i][j] = YES;
                if(i < xs.size()-2 && board[i+1][j] == YES) board[i][j] = YES;
                if(board[i][j] == IDK) {
                    total += ((long long int) xs[i+1] - (long long int) xs[i]) * ((long long int) ys[j+1] - (long long int) ys[j]);
                }
            }
        }
        cout << "Case " << testcase << ": " << total << endl;
    }
}
