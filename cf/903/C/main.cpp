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
  vector<ll> ns = get_vector<ll>(n);

  sort(ns.begin(), ns.end());
  vector<int> repeated(n);
  repeated[0] = 1;
  forn(i, 1, n) {
    if(ns[i] == ns[i - 1]) repeated[i] = repeated[i - 1] + 1;
    else repeated[i] = 1;
  }

  cout << *max_element(repeated.begin(), repeated.end()) << endl;



}

