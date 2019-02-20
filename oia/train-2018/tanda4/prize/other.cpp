#include "prize.h"
#include <bits/stdc++.h>
using namespace std;

namespace my {
  static vector<pair<int, int>> buffer;
  int n;
  int v;
}

// Buffered ask()
pair<int, int> get_at(int t) {
  if(my::buffer[t].first == -1) {
    vector<int> res = ask(t);
    my::buffer[t].first = res[0];
    my::buffer[t].second = res[1];
    return my::buffer[t];
  } else return my::buffer[t];

}

int get_rank(int t) {
  return get_at(t).first + get_at(t).second;
}

int breaker(int size, int t) {
  return size * (2 * t + 1) / (2 * my::v + 2);
}

int search_range(int b, int e) {
  int size = e - b;
  for(int i = 0; i <= my::v; ++i) {
    for(int j = i + 1; j <= my::v; ++j) {
      if(get_rank(breaker(size, i)) == get_rank(breaker(size, j))) {
        if(get_at(breaker(size, j)).first - get_at(breaker(size, i)).first != 0) {
          int tmp = search_range(breaker(size, i), breaker(size, j));
          if(tmp != -1) return tmp;
        }
        int tmp = search_range(b, breaker(size, i));
        if(tmp != -1) return tmp;
        int tmp = search_range(breaker(size, j), e);
        if(tmp != -1) return tmp;
        return -1;
      }
    }
  }

  assert(false);
}

void set_v() {
  my::v = 10;
  // n >= 2 ^ (2 ^ (v-2))
}

int find_best(int n) {
  my::buffer = vector<pair<int, int>>(n, {-1, -1});
  my::n = n;
  set_v();

  // Cada vez que se invalida lo volvemos a hacer
  while(search_range(0, n - 1));

  // Entonces ahora todos los elementos en [0; n-1] con rank menor
  // a curr_max estan askeados. Esto incluye el diamante. Entonces
  // buscamos al de rank 0
  for(int i = 0; i < n; ++i) {
    if(my::buffer[i] == make_pair(0, 0)) return i;
  }

  // Imposible llegar aca si el algoritmo es correcto
  return -1;
}
