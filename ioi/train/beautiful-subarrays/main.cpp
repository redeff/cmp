#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Num {
	int val;
	ll times;
};


ll pair_xor(vector<Num> &as, vector<Num> &bs) {
	ll total = 0;
	int a = 0;
	int b = 0;
	while(a < as.size() && b < bs.size()) {
		if(as[a].val == bs[b].val) {
			total += as[a].times * bs[b].times;
			a++; b++;
		}
		else if(as[a].val < bs[b].val) a++;
		else b++;
	}
	return total;
}

vector<int> ones_of(int k) {
	vector<int> res;
	for(int i = 1; i <= k; i = i << 1) {
		if(i & k) res.push_back(i);
	}
	return res;
}

void compress(vector<Num> &ns) {
    int j = 0;
    for(int i = 1; i < ns.size(); ++i) {
        if(ns[i].val == ns[j].val) ns[j].times += ns[i].times; 
        else {
            j++;
            ns[j] = ns[i];
        }
    }

    for(int i = j; j < ns.size() - 1; ++i) ns.pop_back();
}

ll masked(vector<Num> as, vector<Num> bs, ll k, ll one) {
	ll mask = ~(one - 1);

	for(int i = 0; i < as.size(); ++i) as[i].val &= mask;
	for(int i = 0; i < bs.size(); ++i) bs[i].val &= mask;

	compress(as);
	compress(bs);

	for(int i = 0; i < bs.size(); ++i) bs[i].val ^= one;

	for(int i = 0; i < bs.size() - 1; ++i) 
		if(bs[i].val > bs[i+1].val) swap(bs[i], bs[i+1]);

	return pair_xor(as, bs);
}

ll less_than_k(vector<Num> as, ll k) {
	int n = as.size();
	vector<int> ones = ones_of(k);

	vector<Num> bs = as;
	for(int i = 0; i < n; ++i) {
		bs[i].val = bs[i].val ^ k;
	}

	sort(as.begin(), as.end(), [&](Num a, Num b) {return a.val < b.val;});
	sort(bs.begin(), bs.end(), [&](Num a, Num b) {return a.val < b.val;});

	compress(as);
	compress(bs);

	ll total = 0;
	for(ll one : ones) {
		total += masked(as, bs, k, one);
	}
	;
	return total;
}

int main() {
	ll n; ll k;
	cin >> n >> k;
	vector<Num> as(n + 1);
	int acc = 0;
	as[0].val = acc;
	as[0].times = 1;
	for(int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		acc ^= tmp;
		as[i+1].val = acc;
		as[i+1].times = 1;
	}
	compress(as);
	ll l = less_than_k(as, k);
	if(k != 0) l -= n+1ll;
	l /= 2ll;
	ll m = (n*(n+1ll))/2ll - l;
	
	cout << m << endl;
}
