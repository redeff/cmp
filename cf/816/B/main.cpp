#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
void get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

struct Edge {
  bool begins;
  ll point;
  bool operator<(Edge e){
    return point < e.point;
  }
  Edge(bool begins, ll point){
    this->begins = begins;
    this->point = point;
  }
};

int main(){
  //Get edges
  ll n, k, q_;
  cin >> n >> k >> q_;
  vector<Edge> es;
  vector<pair<ll, ll>> qs;
  forn(i, 0, n){
    ll l, r;
    cin >> l >> r;
    es.emplace_back(true, l);
    es.emplace_back(false, r + 1);
  }
  forn(i, 0, q_){
    ll l, r;
    cin >> l >> r;
    qs.emplace_back(l, r + 1);
  }

  sort(es.begin(), es.end());
  vector<ll> borders;
  ll depth = 0;
  vector<ll> b, e;
  forn(i, 0, es.size()){
    if(es[i].begins){
      depth++;
      if(depth == k){
        b.push_back(es[i].point);
      }
    } else {
      if(depth == k){
        e.push_back(es[i].point);
      }
      depth--;
    }
  }

  vector<ll> s;
  s.push_back(0);
  forn(i, 0, b.size()){
    s.push_back(s.back() + e[i] - b[i]);
  }

  for(auto q : qs){
    auto x = upper_bound(e.begin(), e.end(), q.first) - e.begin();
    auto y = lower_bound(b.begin(), b.end(), q.second) - b.begin();
    ll total = 0;
    if(x == y) total = 0;
    else {
      //forn(i, x, y){
      //  total += e[i] - b[i];
      //}
      total = s[y] - s[x];
      total -= max(0ll, q.first - b[x]);
      total -= max(0ll, e[y - 1] - q.second);
    }
    cout << total << endl;
  }

}
