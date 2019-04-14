#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
 main() {
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		vector<string> s(n);
		int mxlen = 0;
		for(string &a : s) {
			cin >> a;
			reverse(a.begin(), a.end());
			mxlen = max(mxlen, a.size());
		}
		sort(s.begin(), s.end());
		for(int len = mxlen; len > 0; --len) {
			for(string &a : s) if(a.size() == len) a.pop_back();
		}
	}
}
*/

bool has_equal(vector<vector<ll>> &vs) {
	ll n = vs.size();
	return vs.size() >= 2 && vs[n-1].size() == vs[n-2].size() && vs[n-1].back() == vs[n-2].back();
}

ll testcase(vector<vector<ll>> &vs) {
	ll total = 0;
	ll n = 0;
	for(auto &v : vs) n = max(n, (ll) v.size());
	while(!vs.empty() && !vs.back().empty()) {
		// cerr << "LOOP" << endl;
		/*
		for(auto &v : vs) {
			for(ll i : v) cerr << i << " ";
			cerr << endl;
		}
		*/
		vector<vector<ll>> aux;
		while(!vs.empty()) {
			if(has_equal(vs)) {
				// cerr << "INNER LOOP" << endl;
				while(has_equal(vs)) {
					vs.pop_back();
					// cerr << "INNER INNER LOOP" << endl;
				}
				vs.pop_back();
				total++;
			} else {
				aux.emplace_back();
				swap(aux.back(), vs.back());
				vs.pop_back();
			}
		}
		swap(vs, aux);

		for(auto &v : vs) if(v.size() == n) v.pop_back();
		n--;
	}
	return total;
}

int main() {
	int t;
	cin >> t;
	for(ll i = 0; i < t; ++i) {
		ll n;
		cin >> n;
		vector<vector<ll>> s(n);
		for(vector<ll> &v : s) {
			string a;
			cin >> a;
			reverse(a.begin(), a.end());
			ll mod = 1000000007ll;
			ll left = 33948757ll;
			for(char c : a) {
				left *= 4398ll;
				left %= mod;
				// left += (ll) c;
				left ^= (ll) c;
				left %= mod;
				v.push_back(left);
			}
		}
		sort(s.begin(), s.end());
		cout << "Case #" << i + 1 << ": " << 2 * testcase(s) << endl;
	}
}

