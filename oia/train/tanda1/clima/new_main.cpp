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


template<class T, class F>
function<bool (int, int)> deref_cmp(vector<T> ts, F f) {
  return [&](int a, int b) {
    return f(ts[a], ts[b]);
  };
}

vector<int> inv_per(vector<int> &ns) {
  vector<int> inv(ns.size());
  for(int i = 0; i < ns.size(); ++i) {
    inv[ns[i]] = i;
  }
  return ns;
}

// (A, B); A : iota(sort(ts)) -> iota(ts); B : iota(ts) -> iota(sort(ts))
template<class T, class F>
pair<vector<int>, vector<int>> sort_index(vector<T> &ts, F f) {
  vector<int> indices(ts.size());
  iota(indices.begin(), indices.end(), 0);

  sort(indices.begin(), indices.end(), [&](int a, int b) {
      return f(ts[a], ts[b]);
  });

  return {indices, inv_per(indices)};
}


// Hacer una función que dados un conjunto de T
// y dos ordenamientos comp1 y comp2, determine
// por cada T a cuantos es mayor en ambos en tiempo
// O(n), sabiendo que no hay t1 y t2 que sean
// iguales bajo los dos ordenamientos
template<class N, class F1, class F2>
vector<int> count_lower(vector<N> ns, F1 cmp1, F2 cmp2) {
  int n = ns.size();
  vector<int> ft(n + 1, 0);
  vector<int> cmp1_ns, ns_cmp1;
  tie(cmp1_ns, ns_cmp1) = sort_index(ns, cmp1);

  vector<int> cmp2_cmp1, cmp1_cmp2;
  tie(cmp2_cmp1, cmp1_cmp2) = sort_index(cmp1_ns, deref_cmp(ns, cmp2));

  vector<int> lower(n); // lower : iota(ns) -> int
  for(int i = 0; i < n; ++i) { // i in iota(cmp2(cmp1(ns)))
    // FT in cmp1(ns)
    set_ft(cmp2_cmp1[i], ft);
    lower[cmp1_ns[cmp2_cmp1[i]]] = get_ft(cmp2_cmp1[i], ft);
  }

  return lower;
}


int main(){

}

