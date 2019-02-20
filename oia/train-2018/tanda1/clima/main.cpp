#include <bits/stdc++.h>
using namespace std;

vector<int> iot(int n) {
  vector<int> out(n);
  iota(out.begin(), out.end(), 0);
  return out;
}

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

vector<int> inv_per(vector<int> &&ns) {
  vector<int> inv(ns.size());
  for(int i = 0; i < ns.size(); ++i) {
    inv[ns[i]] = i;
  }
  return inv;
}

// (A, B); A : iota(sort(ts)) -> iota(ts); B : iota(ts) -> iota(sort(ts))
template<class F>
vector<int> iotsort(F f, int n) {
  vector<int> indices = iot(n);
  stable_sort(indices.begin(), indices.end(), f);
  return indices;
}

template<class OrdA, class OrdB>
function<bool (int, int)> join(OrdA a, OrdB b) {
  return [&](int n, int m) {
    if(a(n, m)) {
      return true;
    } else if(a(m, n)) {
      return false;
    } else {
      return b(n, m);
    }
  };
}

template<class F>
bool eq(F f, int a, int b) {
  return !f(a, b) && !f(b, a);
}

/*void dbg_vec(vector<int> v) {
  for(int i : v) {
    ofs << i << " ";
  }
  ofs << endl;
}*/

// Hacer una función que dados un conjunto de T
// y dos ordenamientos comp1 y comp2, determine
// por cada T a cuantos es mayor en ambos en tiempo
// O(n), sabiendo que no hay t1 y t2 que sean
// iguales bajo los dos ordenamientos
template<class OrdA, class OrdB>
vector<int> count_lower_strict(OrdA a, OrdB b, int n) {
  vector<int> out(n);
  vector<int> ft(n + 1, 0);
  auto as = iotsort(a, n);
  auto ibs = inv_per(iotsort(b, n));

  for(int i = 0; i < n; ++i) {
    set_ft(ibs[as[i]], ft);
    //dbg_vec(ft);
    out[as[i]] = get_ft(ibs[as[i]], ft);
  }

  return out;
}

template<class OrdA, class OrdB>
vector<int> count_lower(OrdA a, OrdB b, int n) {
  auto ord = iotsort(join(a, join(b, less<int>{})), n);
  auto ls = count_lower_strict(join(a, join(b, less<int>{})), join(b, less<int>{}), n);
  vector<int> out(n);
  for(int i = 0; i < n; ++i) {
    //dbg_vec(out);
    if(i != 0 && eq(join(a, b), ord[i], ord[i - 1])) {
      out[ord[i]] = out[ord[i - 1]];
    } else {
      out[ord[i]] = ls[ord[i]];
    }
  }
  return out;
}

template<class Ord>
vector<int> count_eq(Ord o, int n) {
  auto ord = iotsort(join(o, less<int>{}), n);
  vector<int> out(n, 1);
  for(int i = 0; i < n; ++i) {
    if(i > 0 && eq(o, ord[i], ord[i - 1])) {
      out[ord[i]] = out[ord[i - 1]] + 1;
    }
  }

  for(int i = n - 1; i >= 0; --i) {
    if(i < n - 1 && eq(o, ord[i], ord[i + 1])) {
      out[ord[i]] = out[ord[i + 1]];
    }
  }

  return out;
}

struct Estacion {
  int p;
  int q;
  Estacion(int p, int q): p(p), q(q) {}
};

bool cmp1(Estacion a, Estacion b) {
  return a.p < b.p;
}

bool ncmp1(Estacion a, Estacion b) {
  return a.p > b.p;
}

bool cmp2(Estacion a, Estacion b) {
  return a.q < b.q;
}

bool ncmp2(Estacion a, Estacion b) {
  return a.q > b.q;
}

int main(){
  ifstream ifs;
  ifs.open("clima.in");
  ofstream ofs;
  ofs.open("clima.out");

  int n;
  ifs >> n;

  vector<Estacion> es;

  for(int i = 0; i < n; ++i) {
    int p = 33333333; // Minima
    int q = -33333333; // Maxima
    int r;
    ifs >> r;
    for(int j = 0; j < r; ++j) {
      int pl, ql;
      ifs >> pl >> ql;
      p = min(p, pl);
      q = max(q, ql);
    }

    es.emplace_back(-p, q);
  }

  auto lt = count_lower(
      [&](int a, int b) { return cmp1(es[a], es[b]); },
      [&](int a, int b) { return cmp2(es[a], es[b]); },
      es.size()
  );

  auto gt = count_lower(
      [&](int a, int b) { return ncmp1(es[a], es[b]); },
      [&](int a, int b) { return ncmp2(es[a], es[b]); },
      es.size()
  );

  auto et = count_eq(
      [&](int a, int b) { return make_pair(es[a].p, es[a].q) < make_pair(es[b].p, es[b].q); },
      es.size()
  );

  //dbg_vec(lt);
  //dbg_vec(gt);
  //dbg_vec(et);

  vector<int> maxs;
  for(int i = 0; i < es.size(); ++i) {
    if(maxs.empty() || lt[maxs.back()] < lt[i]) {
      maxs = {i};
    } else if (lt[maxs.back()] == lt[i]) {
      maxs.push_back(i);
    }
  }
  for(auto m : maxs) {
    ofs << m + 1 << " " << n - lt[m] - gt[m] - et[m] << endl;
  }
}
