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
  int n;
  cin >> n;
  auto ns = get_vector<int>((ll) n);

  bool even = true;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < i; ++j) {
      if(ns[j] > ns[i]) even = !even;
    }
  }

  int m;
  cin >> m;
  for(int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    int d = r - l + 1;
    if(((d * (d - 1)) / 2) % 2 == 1) even = !even;
    if(even) {
      cout << "even" << endl;
    } else {
      cout << "odd" << endl;
    }
  }
}

