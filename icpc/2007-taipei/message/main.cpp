#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int T = N * N;

bitset<T> inp() {
	bitset<T> out;
	for(int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < N; ++j) out[i*N+j] = s[j] == '1';
	}

	return out;
}

bitset<T> rot(bitset<T> a) {
	bitset<T> out;
	for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) {
		out[N*j + N-i-1] = a[N*i + j];
	}

	return out;
}

int main() {
	int n;
	cin >> n;

	string en;
	vector<bitset<T>> al;

	for(int i = 0; i < n; ++i) {
		string c;
		cin >> c;
		auto b = inp();
		en.push_back(c[0]);
		en.push_back(c[0]);
		en.push_back(c[0]);
		en.push_back(c[0]);

		al.push_back(b);
		b = rot(b);
		al.push_back(b);
		b = rot(b);
		al.push_back(b);
		b = rot(b);
		al.push_back(b);
	}

	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		auto b = inp();
		vector<int> res(4*n);
		for(int j = 0; j < 4*n; ++j) {
			res[j] = (b ^ al[j]).count();
		}
		int ind = min_element(res.begin(), res.end()) - res.begin();
		cout << en[ind];
	}
	cout << endl;
}
