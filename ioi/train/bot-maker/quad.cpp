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
        vector<vector<Poss>> board(n, vector<Poss>(m, IDK));
        board.back().back() = YES;

        // vector<Rect> rects;
        for(int i = 0; i < w; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            /*
            rects.push_back(Rect{.x1=x1, .x2=x2, .y1=y1, .y2=y2});
            diffys.insert(y1);
            diffys.insert(y2+1);
            diffxs.insert(x1);
            diffxs.insert(x2+1);
            */
            for(int x = x1; x <= x2; ++x) for(int y = y1; y <= y2; ++y) {
                board[x][y] = NO;
            }
        }
        
        long long int total = 0;

        int xsz = board.size();
        int ysz = board.back().size();
        for(int x = xsz - 1; x >= 0; --x) {
            for(int y = ysz - 1; y >= 0; --y) {
                if(board[x][y] != IDK) continue;
                if(x + 1 < xsz && board[x+1][y] == YES) board[x][y] = YES;
                if(y + 1 < ysz && board[x][y+1] == YES) board[x][y] = YES;
                if(board[x][y] == IDK) {
                    total++;
                }
            }
        }
        cout << "Case " << testcase << ": " << total << endl;
    }
}
