#include <bits/stdc++.h>
using namespace std;

const int VOL = 5001;
const int SOL = 1001;

struct ChemicalMixing {
	double closestBlend(vector <int> volume, vector <int> solute, int minVolume, double desiredStrength) {
		bool dp[VOL][SOL][2];
		for(int i = 0; i < VOL; ++i) for(int j = 0; j < SOL; ++j) dp[i][j][1] = false;
		dp[0][0][1] = true;

		int n = volume.size();
		int last = 1;
		for(int i = 0; i < n; ++i) {
			last = i%2;
			for(int x = 0; x < VOL; ++x) for(int y = 0; y < SOL; ++y) {
				dp[x][y][i%2] = dp[x][y][(i+1)%2];
				if(x - volume[i] >= 0 && y - solute[i] >= 0) {
					dp[x][y][i%2] = dp[x][y][i%2] || dp[x-volume[i]][y-solute[i]][(i+1)%2];
				}
			}
		}

		bool uni = true;
		double best_st = -1.0;
		for(int x = minVolume; x < VOL; ++x) for(int y = 0; y < SOL; ++y) {
			if(dp[x][y][last]) {
				double st = abs(desiredStrength - double(y)/double(x));
				if(uni) {
					uni = false;
					best_st = st;
				} else {
					best_st = min(best_st, st);
				}
			}
		}

		return best_st;
	}
};
