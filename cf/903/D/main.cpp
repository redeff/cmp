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

ll lsb(ll x) {
  return x & -x;
}

// Toma la suma de los valores del
// array en [0, index)
ll sum_ft(ll index, vector<ll> &ft) {
  ll v = 0;
  for(ll x = index; x > 0; x -= lsb(x)) {
    v += ft[x];
  }
  return v;
}

// Aumenta en 1 el valor en indice $index
void add_ft(ll index, vector<ll> &ft) {
  index += 1;
  for(ll x = index; x < ft.size(); x += lsb(x)) {
    ft[x] += 1;
  }
}

void dbg(vector<ll> ns) {
  for(n : ns) {
    cerr << n << " ";
  } cerr << endl;
}

int main(){
  ll n;
  cin >> n;
  vector<ll> ns = get_vector<ll>(n);
  // sort(ns.begin(), ns.end());
  vector<ll> temp;
  for(auto ene : ns) {
    temp.push_back(ene);
    temp.push_back(ene + 1);
    temp.push_back(ene - 1);
  }
  sort(temp.begin(), temp.end());
  auto it = unique(temp.begin(), temp.end());
  temp.resize(it - temp.begin());
  unordered_map<ll, ll> index;
  forn(i, 0, temp.size()) {
    index[temp[i]] = i;
  }
  
  ll total = 0;

  // Up
  {
    vector<ll> ft(temp.size() + 1);
    forn(i, 0, n) {
      add_ft(index[ns[i]], ft);
      total += ns[i] * (1 + i - sum_ft(index[ns[i]] + 2, ft) + sum_ft(index[ns[i]] - 1, ft));
    }
  }

  // Down
  {
    vector<ll> ft(temp.size() + 1);
    for(ll i = n - 1; i >= 0; --i) {
      add_ft(index[ns[i]], ft);
      total -= ns[i] * (n - i - sum_ft(index[ns[i]] + 2, ft) + sum_ft(index[ns[i]] - 1, ft));
    }
  }

  cout << total << endl;
}

