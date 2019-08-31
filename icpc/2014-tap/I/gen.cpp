#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < n; ++i)

const int BOUND = 1e7;

int sieve[BOUND];
bool feo[BOUND];

int main() {
	for(int p = 2; p < BOUND; ++p) if(sieve[p] == 0) {
		for(int k = p; k < BOUND; k += p) if(sieve[k] == 0) {
			sieve[k] = p;
		}
	}

	function<void(int, int)> dfs = [&](int l, int r) {
		feo[l] = true;
		feo[r] = true;
		fore(i, l+1, r) {
			if(i - sieve[i] <= l && i + sieve[i] >= r) {
				feo[i];
				dfs(l, i);
				dfs(i, r);
				return;
			}
		}
	};
	int last = 1;
	fore(i, 2, BOUND) {
		if(sieve[i] == i || i == BOUND-1) {
			dfs(i, last);
			last = i;
		}
	}

	vector<pair<int, int>> total;
	last = 1;
	fore(i, 2, BOUND) {
		if(feo[i]) {
			for(int j = last+1; j < i; ++j) {
				for(int k = j+1; k <= i; ++k) {
					for(int l = j; l < k; ++l) {
						if(l - sieve[l] < j && l + sieve[l] >= k) goto fal;
					}
					total.push_back({j, k});
				fal:;
				}
			}
			last = i;
		}
	}
	for(auto p : total) cout << "{" << p.first << ", " << p.second-1 << "}," << endl;
}
