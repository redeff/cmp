#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
vector<T> get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

int main(){
  ll n;
  cin >> n;
  auto ns = get_vector<ll>(n);

  ll mn = *min_element(ns.begin(), ns.end());
  vector<ll> mns;
  forn(i, 0, n) {
    if(ns[i] == mn) mns.push_back(i);
  }

  ll mn_dist = 333333333333;
  forn(i, 1, mns.size()) {
    mn_dist = min(mn_dist, mns[i] - mns[i - 1]);
  }

  cout << mn_dist << endl;

}

