#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void testcase() {
  ll n, k;
  cin >> n >> k;
  if(k != 0) {
    vector<ll> with_n_boys_before = {1};
    for(ll i = 0; i < n; ++i) {
      char c;
      cin >> c;
      if(c == '1') {
        with_n_boys_before.push_back(1);
      } else {
        with_n_boys_before.back()++;
      }
    }

    ll total = 0;
    for(ll i = 0; i < ll(with_n_boys_before.size()) - k; ++i) {
      total += with_n_boys_before[i] * with_n_boys_before[i + k];
    }
    cout << total << endl;
  } else {
    vector<ll> groups;
    string s;
    cin >> s;
    for(ll i = 0; i < ll(s.size()); ++i) {
      if(s[i] == '0') {
        if(i == 0 || s[i - 1] == '1') groups.push_back(1);
        else groups.back()++;
      }
    }
    ll total = 0;
    for(auto g : groups) total += (g * (g - 1)) / 2 + g;
    cout << total << endl;
  }
}

int main() {
  int T;
  cin >> T;
  for(int i = 0; i < T; ++i) testcase();
}
