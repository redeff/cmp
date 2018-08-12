#include <bits/stdc++.h>
using namespace std;

/*
struct Linear {
    double a;
    double b;
};

Linear join(Linear x, Linear y, double proba) {
    return {x.a * proba + y.a * (1.0-proba),
        x.b * proba + y.b * (1.0-proba)};
}
*/

struct ProbabilisticAlice {
    double computeExpectation(vector <string> grid, int pnum, int pden) {
        int c = grid.size();
        int r = grid.back().size();
        double p = (double)pnum / (double)pden;
        vector<vector<double>> dp(c, vector<double>(r));
        for(int x = c-1; x >= 0; --x) {
            for(int y = r-1; y >= 0; --y) {
                if(y == r-1 && x == c-1) {
                    dp[x][y] = 1.0; 
                } else if(grid[x][y] == 'T') {
                    dp[x][y] = 0.0; 
                } else if(y == r-1) dp[x][y] == dp[x+1][y];
                else if(x == c-1) dp[x][y] == dp[x][y+1];
                else {
                    dp[x][y] = p * dp[x+1][y] + (1.0-p) * dp[x][y+1];
                }
            }
        }

        double pfin = dp[0][0];
        if(pfin < 1e-58) return -1;
        else return (1.0 - pfin) / pfin;
    }
};
