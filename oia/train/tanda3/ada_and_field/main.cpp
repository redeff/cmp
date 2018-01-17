#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct CompareGaps {
  bool operator() (const pair<ll, ll>& a, const pair<ll, ll>& b) const {
    if(a.second - a.first == b.second - b.first) {
      return a.first < b.first;
    } else {
      return a.second - a.first < b.second - b.first;
    }
  }
};

struct BiggestGap {
  set<pair<ll, ll>, CompareGaps> gaps;
  set<ll> points;

  BiggestGap(ll n) {
    points = {0, n};
    gaps = {{0, n}};
  }

  ll max_gap() {
    auto gap = *gaps.rbegin();
    return gap.second - gap.first;
  }

  void add_point(ll p) {
    if(points.count(p) > 0) return;
    points.insert(p);
    ll a = *prev(points.find(p));
    ll b = *next(points.find(p));
    gaps.erase({a, b});
    gaps.insert({a, p});
    gaps.insert({p, b});
  }
};

/*
ll main() {
  auto gapper = BiggestGap(10);
  cout << gapper.max_gap() << endl;
  gapper.add_poll(5);
  cout << gapper.max_gap() << endl;
  gapper.add_poll(4);
  cout << gapper.max_gap() << endl;
  gapper.add_poll(7);
  cout << gapper.max_gap() << endl;
}
*/

void testcase() {
  ll n, m, q;
  cin >> n >> m >> q;
  auto x_gapper = BiggestGap(n);
  auto y_gapper = BiggestGap(m);
  for(ll i = 0; i < q; ++i) {
    ll c, v;
    cin >> c >> v;
    (c == 0 ? x_gapper : y_gapper).add_point(v);
    /*if(c == 0) x_gapper.add_point(v);
    else y_gapper.add_point(v);*/
    cout << x_gapper.max_gap() * y_gapper.max_gap() << endl;
  }
}

int main() {
  ll T;
  cin >> T;
  for(ll i = 0; i < T; ++i) testcase();
}
