#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

const int powr = 1594323;
int dp[powr];
const int bound = 13;
const int pos = 3;

int hsh(int arr[bound]) {
	int res = 0;
	for(int i = 0; i < bound; ++i) {
		res *= pos;
		res += arr[i];
	}
	assert(res < powr);
	return res;
}

int rec(int arr[bound]) {
	int h = hsh(arr);
	if(dp[h] != 0) return dp[h];
	dp[h] = 1;
	forn(i, bound) if(arr[i] != 0) {
		arr[i]--;
		forn(j, i+1) if(arr[j] != 0) {
			arr[j]--;
			forn(k, j+1) if(arr[k] != 0 && 2+k+j > 1+i) {
				arr[k]--;
				dp[h] = max(dp[h], 1+rec(arr));
				arr[k]++;
			}
			arr[j]++;
		}
		arr[i]++;
	}
	return dp[h];
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	while(cin >> n && n != 0) {
		int arr[2][bound];
		forn(i, 2) forn(j, bound) arr[i][j] = 0;

		forn(i, n) {
			int k;
			cin >> k;
			arr[i%2][k-1]++;
		}

		int points[2] = {0,0};
		forn(i, 2) {
			forn(j, bound) {
				points[i] += arr[i][j]/3*(n+100);
				arr[i][j] %= 3;
			}
			points[i] += rec(arr[i]);
		}
		
		if(points[0] == points[1]) cout << 0 << "\n";
		else if(points[0] < points[1]) cout << 2 << "\n";
		else cout << 1 << "\n";
		
	}
}
