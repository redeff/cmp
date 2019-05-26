#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int INF = 33333333;

ll mer(vector<int> &ns) {
	ll total = 0;

	int n = (int) ns.size();
	if(n < 2) return 0;

	vector<int> as(n/2);
	for(int i = 0; i < n/2; ++i) as[i] = ns[i];
	total += mer(as);
	as.push_back(INF);

	vector<int> bs(n-n/2);
	for(int i = n/2; i < n; ++i) bs[i-n/2] = ns[i];
	total += mer(bs);
	bs.push_back(INF);

	int a = 0;
	int b = 0;
	for(int i = 0; i < n; ++i) {
		if(as[a] < bs[b]) {
			ns[i] = as[a++];
			total += b;
		} else {
			ns[i] = bs[b++];
		}
	}

	return total;
}

int main() {
	int n;
	cin >> n;
	vector<int> ns(n);
	for(int &i : ns) {
		cin >> i;
		--i;
	}
	{
		auto merg = ns;
		cout << mer(merg);
		cout << endl;
	}

	vector<int> cyc(n, -1);
	int cycs = 0;
	for(int i = 0; i < n; ++i) if(cyc[i] == -1) {
		cycs++;
		cyc[i] = i;
		for(int j = ns[i]; j != i; j = ns[j]) cyc[j] = i;
	}
	cout << n - cycs << endl;

	int index = n-1;
	int times = 0;
	for(int i = n-1; i >= 0; --i) {
		if(ns[i] == index) {
			index--;
			times++;
		}
	}

	vector<int> dp = {-1};
	for(int i = 0; i < n; ++i) {
		auto it = lower_bound(dp.begin(), dp.end(), ns[i]);
		if(it == dp.end()) dp.push_back(ns[i]);
		else *it = ns[i];
	}

	cout << n - dp.size() + 1 << endl;
	cout << n - times << endl;
}
