#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

//Black and white
struct Baw {
  ll hi_w;
  ll lo_w;
  ll hi_b;
  ll lo_b;

  Baw(ll hi_w, ll lo_w, ll hi_b, ll lo_b):
    hi_w(hi_w),
    lo_w(lo_w),
    hi_b(hi_b),
    lo_b(lo_b)
  {}

  bool operator==(const Baw & other) const {
    return
      hi_w == other.hi_w &&
      lo_w == other.lo_w &&
      hi_b == other.hi_b &&
      lo_b == other.lo_b;
  }

  ll mini() {
    return min(lo_w, lo_b);
  }
};

namespace std {
  template <> struct hash<Baw> {
    size_t operator()(const Baw & a) const {
      return
        hash<ll>()(a.hi_w) ^
        hash<ll>()(a.lo_w) ^
        hash<ll>()(a.hi_b) ^
        hash<ll>()(a.lo_b);
    }
  };
}

unordered_map<Baw, ll> dp;
vector<ll> lens;

bool work(ll min, ll mid, ll max) {
  return 2 * mid > min + max;
}

ll get(Baw a){
  if(dp.count(a) > 0){
    return dp[a];
  } else {
    ll result = 0;
    ll low = a.mini();
    if(low == 0){
      result = 1;
    } else {
      if(work(lens[a.hi_w], lens[a.lo_w], lens[low - 1])){
        result += get(Baw(a.lo_w, low - 1, a.hi_b, a.lo_b));
      }
      
      if(work(lens[a.hi_b], lens[a.lo_b], lens[low - 1])){
        result += get(Baw(a.hi_w, a.lo_w, a.lo_b, low - 1));
      } 
    }

    dp[a] = result;
    return result;
  }
}

int main(){
  while(true){
    lens.clear();
    dp.clear();
    ll n;
    cin >> n;
    if(n == -1) return 0;
    lens.resize(n);
    for(ll i = 0; i < n; ++i){
      cin >> lens[i];
    }

    lens.push_back(0);
    lens.push_back(0);

    n = lens.size();

    sort(lens.begin(), lens.end());

    if(lens[n - 1] == lens[n - 2] && lens[n - 2] == lens[n - 3]){
      cout << 0 << endl;
      continue;
    }

    ll rep = 1;
    ll perm = 1;
    for(ll i = 0; i < n; ++i){
      if(i > 0 && lens[i] == lens[i - 1]){
        rep++;
        perm *= rep;
      } else {
        rep = 1;
      }
    }

    cout << get(Baw(0, n - 1, 0, n - 1)) / perm << endl;
  }
}
