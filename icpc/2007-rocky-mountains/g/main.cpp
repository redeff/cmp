#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 25;
const int MAX_STICKS = 13;
const int MAX_TOTAL_LEN = MAX_LEN * MAX_STICKS;

int main() {
	vector<bool> dp[MAX_TOTAL_LEN + 1][MAX_LEN + 1];
	int n;
	int cas = 0;
	while(cin >> n && n != 0) {
		cas++;
		vector<int> ns(n);
		for(int & i : ns) cin >> i;
		for(int i = 0; i <= MAX_TOTAL_LEN; ++i)
			for(int j = 0; j <= MAX_LEN; ++j)
				dp[i][j] = vector<bool> (1 << MAX_STICKS, false);

		int best = 0;
		
		// dp[0][0][0] = true;
		function<void(int, int, int, int, int)> dfs = [&](int st, int a, int b, int c, int mx) {
			assert(a >= 0);
			assert(b >= 0);
			assert(c >= 0);
			if(a < b) swap(a, b);
			if(a < c) swap(a, c);
			if(b < c) swap(b, c);
			assert(a - b <= MAX_LEN);
			assert(a - c <= MAX_LEN);
			assert(a >= b && b >= c);
			assert(st < 1 << n);
			// cerr << st << " " << mx_len << " " << a << " " << b << endl;
			if(dp[a][a - b][st]) return;
			dp[a][a - b][st] = true;
			// cerr << "inside" << endl;
			bool cont = (a != c && b != c) || c == 0;
			/*
			cout
				<< std::bitset<13>(st)
				<< " " << a
				<< " " << b
				<< " " << c
				<< " " << (cont?'.':'#')
				<< endl;
				*/
			if(cont) {
				for(int i = 0; i < n; ++i) {
					if(((st & (1 << i)) == 0) /*&& c + ns[i] >= a*/)
						dfs(st | (1 << i), a, b, c + ns[i], max(mx, ns[i]));
				}
			} else if(a == c && a != mx) best = max(best, a);
		};

		// dfs(3, ns[0], ns[0], ns[0]);
		dfs(0, 0, 0, 0, 0);

		cout << "Case " << cas << ": " << best << endl;
	}
}
