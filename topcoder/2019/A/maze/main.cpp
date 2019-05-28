#include <bits/stdc++.h>
using namespace std;

class FillInTheMaze {
public:
    vector<string> filled(int r, int c, int x) {
        vector<string> maze(2*r + 1, string(2*c + 1, '#'));
        for(int i = 1; i < 2*r+1; i += 2) {
            for(int j = 1; j < 2*c; j += 1) {
                maze[i][j] = '.';
            }
        }

        for(int i = 1; i < 2*r; i += 1) {
            maze[i][1] = '.';
        }

        for(int i = 1; i < 2*r+1; i += 2) {
            if(x-- > 0) maze[i][0] = '.';
            if(x-- > 0) maze[i][2*c] = '.';
        }
        for(int j = 1; j < 2*c+1; j += 2) {
            if(x-- > 0) maze[0][j] = '.';
            if(x-- > 0) maze[2*r][j] = '.';
        }
        return maze;
    }
};
