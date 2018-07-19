#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, p, k;
	cin >> n >> p >> k;
	--k;

	// Colors
	vector<bool> cs(n);
	int bl;
	for(int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		cs[i] = tmp > p;
		if(cs[i]) bl = i;
	}

	vector<vector<int>> tree(n);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	int head = 0;
	for(int i = 0; i < n; ++i) {
		if(tree[i].size() == 1) head = i;
	}

	vector<bool> colors(n);
	int a = head;
	int b = tree[head][0];
	int i = 0;
	while(tree[b].size() == 2) {
		colors[i] = cs[a];
		colors[i + 1] = cs[b];

		int c = tree[b][0] == a ? tree[b][1] : tree[b][0];
		a = b;
		b = c;
		++i;

	}
	colors[n - 1] = cs[b];
	// for(int i = 0; i < n; ++i) cerr << colors[i] << endl;

	vector<int> upto(n + 1);
	upto[0] = 0;
	for(int i = 1; i <= n; ++i) {
		upto[i] = upto[i - 1] + (colors[i - 1] ? 1 : 0);
	}

	int res = 0;
	for(int i = 0; i < n; ++i) {
		int lo1 = i - 1;
		int hi1 = n;
		while(lo1 + 1 < hi1) {
			int mid = (lo1 + hi1) / 2;
			int total = upto[mid] - upto[i];
			if(total < k) lo1 = mid;
			else hi1 = mid;
		}
		int lo2 = i - 1;
		int hi2 = n;
		while(lo2 + 1 < hi2) {
			int mid = (lo2 + hi2) / 2;
			int total = upto[mid] - upto[i];
			if(total <= k) lo2 = mid;
			else hi2 = mid;
		}
		res += lo2 - lo1;
		// cerr << lo2 - lo1 << endl;
	}

	cout << res << endl;
}
