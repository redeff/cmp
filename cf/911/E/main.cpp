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
  int n, k;
  cin >> n >> k;

  auto ns = get_vector<int>((ll) k);
  auto orig = ns;
  reverse(ns.begin(), ns.end());

  vector<int> stac;
  int curr = 1;
  while(!ns.empty()) {
    if(!stac.empty() && stac.back() == curr) {
      stac.pop_back();
      curr++;
    } else {
      stac.push_back(ns.back());
      ns.pop_back();
    }
  }

  stac.push_back(curr - 1);
  reverse(stac.begin(), stac.end());
  stac.push_back(n + 1);

  if(!is_sorted(stac.begin(), stac.end())) {
    cout << -1 << endl;
  } else {
    for(int i = 0; i < int(stac.size()) - 1; ++i) {
      for(int j = stac[i + 1] - 1; j > stac[i]; --j) {
        orig.push_back(j);
      }
    } 
    for(auto t : orig) {
      cout << t << " ";
    } cout << endl;
  }
}

