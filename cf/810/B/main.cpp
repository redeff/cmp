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

int main(){
  ll n, f;
  cin >> n >> f;

  vector<ll> gs;
  ll prods = 0;
  forn(day, 0, n){
    ll k, l;
    cin >> k >> l;
    gs.push_back(min(l, 2*k) - min(l, k));
    prods += min(l, k);
  }
  sort(gs.begin(), gs.end());

  ll total = 0;
  forn(i, 0, f){
    total += gs[n - i - 1];
  }
  cout << total + prods << endl;


}
