#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

void testcase(int n) {
  vector<int> ns;
  forn(i, n) {
    ns.emplace_back();
    cin >> ns.back();
  }

  sort(ns.begin(), ns.end());

  int total = 0;
  vector<int> iot;
  forn(i, n) iot.push_back(i);
  forn(i, n) forn(j, i) {
    // i > j, all possible pairs.
    // Find all k such that k < j and ns[i], ns[j] and ns[k] dont form a trig
    // Those are k < min(j, i - j)
    // int bound = min(ns[j], ns[i] - ns[j]);
    total += lower_bound(iot.begin(), iot.end(), ns[i] - ns[j], [&](int index, int val) {
        return ns[index] < val && index < j;
    }) - iot.begin();
  }

  cout << total << endl;
}

int main() {
  int t;
  while(true) {
    cin >> t;
    if(t == 0) break;
    testcase(t);
  }
}
