#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	int n;
	cin >> n;

	struct Point {
		ll pos;
		bool end;
		int index;
		bool operator<(Point o) {
			if(o.pos != pos) return pos < o.pos;
			return (int) end < (int) o.end;
		}
	};

	vector<Point> ns;
	for(int i = 0; i < n; ++i) {
		ll a, b;
		cin >> a >> b;
		ns.push_back(Point {a, false, i});
		ns.push_back(Point {b, true, i});
	}

	vector<int> res(n, -1);
	vector<int> emp;

	sort(ns.begin(), ns.end());
	int mx = 0;
	for(auto p : ns) {
		if(p.end) {
			emp.push_back(res[p.index]);
		} else {
			if(emp.empty()) {
				mx++;
				emp.push_back(mx);
			}
			res[p.index] = emp.back();
			emp.pop_back();
		}
	}

	cout << mx << endl;
	for(int i : res) cout << i << " ";
	cout << endl;
}
