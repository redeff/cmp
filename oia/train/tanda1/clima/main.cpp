#include <bits/stdc++.h>
using namespace std;

int lsb(int x) {
  return x & -x;
}

// Toma la suma de los valores del
// array en [0, index)
int get_ft(int index, vector<int> &ft) {
  int v = 0;
  for(int x = index; x > 0; x -= lsb(x)) {
    v += ft[x];
  }
  return v;
}

// Aumenta en 1 el valor en indice $index
void set_ft(int index, vector<int> &ft) {
  index += 1;
  for(int x = index; x < ft.size(); x += lsb(x)) {
    ft[x] += 1;
  }
}

#define ins cin
#define ous cout

template<typename T, typename FuncA, typename FuncB>
vector<pair<T, int>> count_greater(vector<T> ns, FuncA comp1, FuncB comp2) { 
  vector<int> ft = vector<int>(ns.size() + 1, 0);
  vector<pair<T, int>> out;
  sort(ns.begin(), ns.end(), comp1);
  stable_sort(ns.begin(), ns.end(), comp2);

  vector<pair<T, int>> with_index;
  for(int i = 0; i < ns.size(); ++i) {
    with_index.emplace_back(ns[i], i);
  }

  stable_sort(
      with_index.begin(), 
      with_index.end(), 
      [&](pair<T, int> t1, pair<T, int> t2) {
        return comp1(t1.first, t2.first);
      }
  );

  for(int i = 0; i < with_index.size(); ++i) {
    set_ft(with_index[i].second, ft);
    out.emplace_back(with_index[i].first, get_ft(with_index[i].second, ft));
  }
  return out;
}

struct Station {
  int mini;
  int maxi;
  Station(int mini, int maxi)
    : mini(mini)
    , maxi(maxi)
  {}
}

vector<int> inv_per(vector<int> &ns) {
  vector<int> ps(ns.size());
  for(int i = 0; i < ns.size(); ++i) {
    ps[ns[i]] = i;
  }

  return ps;
}


// Given a list of Ts such that no two of them are equal
// under both comp_a and comp_b, calculate the ones that
// are less than most elements, return their indices, and
// the amount of other Ts they're incomparable with
template<typename T, typename FuncA comp_a, typename FuncB>
vector<pair<int, int>> from_distinct(
    vector<T> ns, 
    FuncA comp_a, 
    FuncB comp_b) {
  vector<int> indices(ns.size());
  iota(indices.begin(), indices.end(), 0);
  sort(
      indices.begin(), 
      indices.end(), 
      [&](int i1, int i2) {
        return comp_a(ns[i1], ns[i2]);
      }
  );
}

int main() {
}

