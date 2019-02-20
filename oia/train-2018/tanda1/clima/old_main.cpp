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

  stable_sort(with_index.begin(), with_index.end(), [&](pair<T, int> t1, pair<T, int> t2) {
    return comp1(t1.first, t2.first);
  });

  for(int i = 0; i < with_index.size(); ++i) {
    set_ft(with_index[i].second, ft);
    out.emplace_back(with_index[i].first, get_ft(with_index[i].second, ft));
  }
  return out;
}

struct Estacion {
  int p;
  int q;
  Estacion(int p_, int q_):
    p(p_), q(q_) {}
};

int main() {
  vector<int> ft(100, 0);
  set_ft(4, ft);
  ous << get_ft(5, ft) << endl;
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

    es.emplace_back(-p, q);
  }

  vector<int> indices;
  for(int i = 0; i < es.size(); ++i) {
    indices.push_back(i);
  }

  vector<int> sorted = indices;
  sort(sorted.begin(), sorted.end(), [&](int a, int b) {
      // Orden lexicografico, los elementos iguales quedan adyacentes
      return make_pair(es[a].p, es[a].q) < make_pair(es[b].p, es[b].q);
  });

  vector<int> inverse_sort(sorted.size());
  for(int i = 0; i < sorted.size(); ++i) {
    inverse_sort[sorted[i]] = i;
  }

  vector<int> diff;
  for(int i = 0; i < sorted.size(); ++i) {
    // Eliminamos elementos iguales
    if(diff.empty() || es[diff.back()].p != es[i].p || es[diff.back()].q != es[i].q) {
      diff.push_back(i);
    }
  }

  // Num win, Num loose, Repeat
  vector<tuple<int, int, int>> out(es.size(), make_tuple(-1, -1, 0));
  auto c = count_greater(
    diff,
    [&] (int a, int b) {
      return es[a].p < es[b].q;
    },
    [&] (int a, int b) {
      return es[a].q < es[b].q;
    }
  );

  for(pair<int, int> p : c) {
    get<0>(out[p.first]) = p.second;
  }
  c = count_greater(
    diff,
    [&] (int a, int b) {
      return es[a].p > es[b].q;
    },
    [&] (int a, int b) {
      return es[a].q > es[b].q;
    }
  );

  for(pair<int, int> p : c) {
    get<1>(out[p.first]) = p.second;
  }

  for(int i = 0; i < out.size(); ++i) {
    cout << get<0>(out[i]) << " ";
    cout << get<1>(out[i]) << " ";
    cout << get<2>(out[i]) << " ";
    cout << endl;
  }
  for(int i = 0; i < out.size(); ++i) {
    if(get<0>(out[i]) == -1) {
      swap(get<0>(out[i]), get<0>(out[sorted[inverse_sort[i] - 1]]));
      get<1>(out[i]) = get<1>(out[sorted[inverse_sort[i] - 1]]);

      get<2>(out[i]) = get<2>(out[sorted[inverse_sort[i] - 1]]) + 1;
    }
  }

  for(int i = 0; i < out.size(); ++i) {
    if(get<0>(out[i]) == -1) {
      get<0>(out[i]) = get<0>(out[sorted[inverse_sort[i] + 1]]);
      get<2>(out[i]) = get<2>(out[sorted[inverse_sort[i] + 1]]);
    }
  }

  int maxi = -333333333;
  for(int i = 0; i < out.size(); ++i) {
    maxi = max(maxi, get<0>(out[i]));
    cout << get<0>(out[i]) << " ";
    cout << get<1>(out[i]) << " ";
    cout << get<2>(out[i]) << " ";
    cout << endl;
  }

  for(int i = 0; i < out.size(); ++i) {
    if(maxi == get<0>(out[i])) {
      ous << i + 1 << " " << (out.size() - 1 - get<0>(out[i]) - get<1>(out[i]));
    }
  }
}
