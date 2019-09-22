#include <bits/stdc++.h>
using namespace std;

pair<int, int> calc(string s) {
	int n = int(s.size());
	vector<int> prev_d(n+1, -1);
	vector<int> prev_r(n+1, -1);

	for(int i = 0; i < n; ++i) {
		if(s[i] == 'D') prev_d[i] = i;
		if(s[i] == 'R') prev_r[i] = i;
		prev_d[i+1] = prev_d[i];
		prev_r[i+1] = prev_r[i];
	}

	int now = max(prev_d.back(), prev_r.back());
	if(now == -1) return {0, 0};

	int index = 0;
	if(s[now] == 'D') index += 2;

	char lst;
	int drs = 0;
	while(now != -1) {
		assert(s[now] == 'D' || s[now] == 'R');
		lst = s[now];
		int nxt = lst == 'D' ? prev_r[now] : prev_d[now];
		if(nxt != -1 && lst == 'R') drs++;
		now = nxt;
	}
	index += lst == 'R';
	return {drs, index};
}

int main() {
	int n;
	while(cin >> n) {
		int a = 0;
		int b = 0;
		int c = 0;
		int total = 0;
		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			auto p = calc(s);
			total += p.first;
			if(p.second == 3) c++;
			if(p.second == 2) a++;
			if(p.second == 1) b++;
		}

		while(c > 1) {
			total++;
			--c;
		}

		while(a && b && c) {
			--a;
			--b;
			--c;
			total += 2;
		}

		total += a + b + c - max(a, max(b, c)) - min(a, min(b, c));
		cout << total << endl;
	}
}
