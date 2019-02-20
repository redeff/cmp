#include <bits/stdc++.h>
using namespace std;

struct PairHash {
  template <class T1, class T2>
  size_t operator () (const pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    return h1 ^ h2;
  }
};

unordered_map<pair<int, int>, pair<pair<int, int>, int>, PairHash> memo;

pair<pair<int, int>, int> f(int zapallos, int index, vector<vector<int>> & precios) {
  if(index == -1) {
    return {{0, 0}, 0};
  } 

  if(memo.count(make_pair(zapallos, index)) > 0) {
    return memo[make_pair(zapallos, index)];
  }

  pair<pair<int, int>, int> maxi = {{-333333333, 0}, 0};
  int sum = 0;
  for(int i = 0; i <= min(zapallos, (int) precios[index].size()); ++i) {
    auto fc = f(zapallos - i, index - 1, precios);
    if(maxi.first < make_pair(fc.first.first + sum, fc.second - i)) {
      maxi.first = make_pair(fc.first.first + sum, fc.second - i);
      maxi.second = i;
    }
    if(i < precios[index].size()) sum += 10 - precios[index][i];
  }
  memo[make_pair(zapallos, index)] = maxi;
  return maxi;
}

// #define ins cin
// #define ous cout

int main() {
  ifstream ins;
  ins.open("zapallos.in");
  ofstream ous;
  ous.open("zapallos.out");

  int a, m;
  ins >> a >> m;
  vector<vector<int>> precios;
  
  for(int i = 0; i < a; ++i) {
    precios.emplace_back();
    int k;
    ins >> k;
    for(int j = 0; j < k; ++j) {
      precios.back().emplace_back();
      ins >> precios.back().back();
    }
  }

  // ous << f(m, a - 1, precios) << endl;
  auto fc = f(m, a - 1, precios);
  ous << fc.first.first << " ";
  vector<int> total(a);
  int zapallos = m;
  for(int i = a - 1; i >= 0; --i) {
    auto l = f(zapallos, i, precios).second;
    zapallos -= l;
    total[i] = l;
  }

  ous << accumulate(total.begin(), total.end(), 0) << endl;
  for(auto i : total) {
    ous << i << " ";
  }
}
