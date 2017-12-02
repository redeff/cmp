#include <bits/stdc++.h>
using namespace std;

// Guarda un array implicito de 1s y 0s
vector<int> ft;

int lsb(int x) {
  return x & -x;
}

// Toma la suma de los valores del
// array en [0, index)
int get_ft(int index) {
  int v = 0;
  for(int x = index; x > 0; x -= lsb(x)) {
    v += ft[x];
  }
  return v;
}

// Aumenta en 1 el valor en indice $index
void set_ft(int index) {
  index += 1;
  for(int x = index; x < ft.size(); x += lsb(x)) {
    ft[x] += 1;
  }
}

#define ins cin
#define ous cout

struct Estacion {
  int p;
  int q;
  int index;

  Estacion(int p_, int q_, int index_):
    p(p_), q(q_), index(index_) {}
};

struct Estaciones {
  int p;
  int q;
  vector<int> is;

  int index;

  Estaciones(int p_, int q_, vector<int> is_, int index_):
    p(p_), q(q_), is(is_), index(index_) {}
};

template<typename T, typename FuncA, typename FuncB>
vector<pair<T, int>> comp(vector<T> ns, FuncA comp1, FuncB comp2) { 
  ft = vector<int>(ns.size() + 1, 0);
  vector<pair<T, int>> out;
  sort(ns.begin(), ns.end(), comp1);
  stable_sort(ns.begin(), ns.end(), comp2);

  vector<pair<T, int>> with_index;
  for(int i = 0; i < ns.size(); ++i) {
    with_index.emplace_back(ns[i], i);
  }

  stable_sort(with_index.begin(), with_index.end(), [&](pair<T, int> t1, pair<T, int> t2) {
    return comp1(t1.first, t2.first);
  });

  for(int i = 0; i < with_index.size(); ++i) {
    set_ft(with_index[i].second);
    out.emplace_back(with_index[i].first, get_ft(with_index[i].second));
  }
  return out;
}

int main() {
  int n;
  ins >> n; // numero de estaciones
  /*vector<pair<int, int>> pairs = {{1, 100}, {3, 4}, {5, 6}};
  auto result = comp(
    pairs, 
    [](pair<int, int> p1, pair<int, int> p2) {
      return p1.first < p2.first;
    },
    [](pair<int, int> p1, pair<int, int> p2) {
      return p1.second < p2.second;
    }
  );
  for(auto r : result) {
    cout << r << endl;
  }*/

  vector<Estacion> es;

  for(int i = 0; i < n; ++i) {
    int p = 33333333; // Minima
    int q = -33333333; // Maxima
    int r;
    cin >> r;
    for(int j = 0; j < r; ++j) {
      int pl, ql;
      cin >> pl >> ql;
      p = min(p, pl);
      q = min(q, ql);
    }

    es.emplace_back(-p, q, i + 1);
  }


  stable_sort(es.begin(), es.end(), [](Estacion a, Estacion b) {
    return a.p < b.p;
  });

  stable_sort(es.begin(), es.end(), [](Estacion a, Estacion b) {
    return a.q < b.q;
  });

  vector<Estaciones> ess;
  int index = 0;
  for(int i = 0; i < n; ++i) {
    if(ess.empty() || ess.back().p != es[i].p || ess.back().q != es[i].q) {
      ess.push_back(Estaciones(es[i].p, es[i].q, {es[i].index}, index));
      index++;
    } else {
      ess.back().is.push_back(es[i].index);
    }
  }

  vector<pair<int, int>> extremes(ess.size());
  for(auto p : comp(
        ess,
        [](Estaciones p1, Estaciones p2) {
          return p1.p < p2.p;
        },
        [](Estaciones p1, Estaciones p2) {
          return p1.q < p2.q;
        }
  )) {
      extremes[p.first.index].first = p.second;
  }
  for(auto p : comp(
        ess,
        [](Estaciones p1, Estaciones p2) {
          return p1.p > p2.p;
        },
        [](Estaciones p1, Estaciones p2) {
          return p1.q > p2.q;
        }
  )) {
      extremes[p.first.index].second = p.second;
  }

  vector<pair<int, int>> total(n);
  for(int i = 0; i < extremes.size(); ++i) {
    total[extremes[i].

  /*stable_sort(es.begin(), es.end(), [](Estacion a, Estacion b) {
    return a.p < b.p;
  });

  vector<int> mas_extremas;
  ft = vector<int>(ess.size() + 1, 0);

  for(int i = 0; i < ess.size(); ++i) {
    set_ft(ess[i].index);
    mas_extremas.push_back(get_ft(ess[i].index));
  }

  vector<int> maximums;
  for(int i = 0; i < mas_extremas.size(); ++i) {
    if(maximums.empty() || mas_extremas[i] > mas_extremas[maximums.back()]) {
      maximums = {i};
    } else if (mas_extremas[i] == mas_extremas[maximums.back()]) {
      maximums.push_back(i);
    }
  }
  for(int m : maximums) {
    cout << "tata" << endl;
    for(int i : ess[m].is) {
      cout << i << " " << mas_extremas[m] << endl;
    }
  }*/
}
