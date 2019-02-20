#include <bits/stdc++.h>
using namespace std;

// Esta funcion calcula, dado un vector, el minimo
// en cada subintervalo de longitud d (basicamente
// el primer problema), y devuelve para cada intervalo
// tanto el valor minimo en si como el indice en el
// que esta en un par
// Es O(n)
template<typename T>
vector<pair<T, int>> mins(int d, const vector<T> &ns) {
  list<int> ls;
  vector<pair<T, int>> out;

  int head = -1;
  int tail = 0;
  auto move_tail = [&ls, &ns, &tail] () {
    if(ls.front() == tail) ls.pop_front();
    tail++;
  };

  auto move_head = [&ls, &head, &ns] () {
    head++;
    while(!ls.empty() && ns[head] < ns[ls.back()]) {
      ls.pop_back();
    }

    ls.push_back(head);
  };

  for(int i = 0; i < d; ++i) {
    move_head();
  }

  out.emplace_back(ns[ls.front()], ls.front());
  for(int i = 0; i < ns.size() - d; ++i) {
    move_head();
    move_tail();
    out.emplace_back(ns[ls.front()], ls.front());
  }

  return out;
}

// Calcula la suma de cada subintervalo de 
// longitud d
// Es O(n)
template<typename T>
vector<T> sums(int d, const vector<T> &ns) {
  vector<T> out;
  T sum = 0;
  for(int i = 0; i < d; ++i) {
    sum += ns[i];
  }

  out.push_back(sum);
  for(int i = 0; i < ns.size() - d; ++i) {
    sum -= ns[i];
    sum += ns[i + d];
    out.push_back(sum);
  }

  return out;
}

// Transpone la matriz de MxN a una de NxM
// Es O(nm)
template<typename T>
vector<vector<T>> flip(const vector<vector<T>> &ns) {
  int xsize = ns.size();
  int ysize = ns[0].size();
  vector<vector<T>> out(ysize, vector<T>(xsize));
  for(int x = 0; x < xsize; ++x) for(int y = 0; y < ysize; ++y) {
    out[y][x] = ns[x][y];
  }
  return out;
}

// Calcula la suma de cada subrectángulo de dx por dy
// de la matriz ns
// O(nm) (n y m dimensiones de ns)
vector<vector<int>> reduce_sums(int dx, int dy, const vector<vector<int>> &ns) {
  vector<vector<int>> out = ns;
  int xsize = ns.size();
  int ysize = ns[0].size();
  for(int x = 0; x < xsize; ++x) {
    out[x] = sums(dy, ns[x]); 
  }
  out = flip(out);
  for(int y = 0; y < ysize - dy + 1; ++y) {
    out[y] = sums(dx, out[y]);
  }
  return flip(out);
}

// Hace lo mismo que la anterior pero en vez de calcular
// la suma calcula el minimo, y sus indices en la matriz
// original, en la forma ((minimo, indice_y), indice_x)
// O(nm)
vector<vector<pair<pair<int, int>, int>>> reduce_mins(int dx, int dy, const vector<vector<int>> &ns) {
  vector<vector<pair<int, int>>> temp(ns.size());
  int xsize = ns.size();
  int ysize = ns[0].size();
  for(int x = 0; x < xsize; ++x) {
    temp[x] = mins(dy, ns[x]); 
  }
  temp = flip(temp);
  vector<vector<pair<pair<int, int>, int>>> out(temp.size());
  for(int y = 0; y < ysize - dy + 1; ++y) {
    out[y] = mins(dx, temp[y]);
  }
  out = flip(out);
  return out;
}

int main() {
  int m, n, a, b, c, d;
  cin >> m >> n >> a >> b >> c >> d;

  vector<vector<int>> board(m, vector<int>(n));

  for(int y = 0; y < n; ++y) {
    for(int x = 0; x < m; ++x) {
      cin >> board[x][y];
    }
  }

  int maxi = 0;
  pair<int, int> best_py;
  pair<int, int> best_ch;
  vector<vector<int>> whole_pyramid_base = reduce_sums(a, b, board);
  vector<vector<int>> chamber = reduce_sums(c, d, board);
  auto min_chamber_in_base = reduce_mins(a - c - 1, b - d - 1, chamber);
  for(int x = 0; x < whole_pyramid_base.size(); ++x) {
    for(int y = 0; y < whole_pyramid_base[x].size(); ++y) {
      pair<pair<int, int>, int> min_chamber = min_chamber_in_base[x + 1][y + 1];
      int this_max_height = whole_pyramid_base[x][y] - chamber[min_chamber.second][min_chamber.first.second];
      if(maxi < this_max_height) {
        maxi = this_max_height;
        best_ch = {min_chamber.second, min_chamber.first.second};
        best_py = {x, y};
      }
    }
  }

  cout << best_py.first + 1 << " " << best_py.second + 1<< endl;
  cout << best_ch.first + 1 << " " << best_ch.second + 1<< endl;
}
