#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Op>
class Fenwick {
  int n; //Length, must be power of 2
  vector<T> vals; //Must be length n

  get(int index){
    T total;
    for(int i = index; i; i -= i & -i){
      total = Op()(total, vals[i]);
    }
    return total;
  }

  set(int index, T delta){
    for(int i = index; i < n; i += i & -i){
      vals[i] = Op(vals[i])

  }
}
