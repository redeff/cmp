#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

// Se guarda qué es cada casilla (pasto, panal, arbol, etc)
vector<vector<char>> board;

// Acá se guarda la distancia de cada
// casilla a los panales de abeja (la distancia
// al panal mas cercano)
vector<vector<int>> dist_to_bees;


int n;
int s;

// La posicion inicial de Mecho
pair<int, int> mecho;

pair<int, int> dirs[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void calc_dist_to_bees() {
  dist_to_bees = vector<vector<int>>(n, vector<int>(n, 33333333));

  // Hacemos bfs
  deque<pair<int, int>> bees;

  // La distancia a los panales en los panales
  // es en sí 0
  forn(i, n) forn(j, n) if(board[i][j] == 'H') {
    bees.emplace_back(i, j);
    dist_to_bees[i][j] = 0;
  }

  while(!bees.empty()) {
    auto p = bees.front();
    bees.pop_front();
    for(auto d : dirs) {
      int nx = p.first + d.first;
      int ny = p.second + d.second;
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if(
          // Condición de que no haya una distancia menor ya puesta en esa casilla
          dist_to_bees[nx][ny] > 
          dist_to_bees[p.first][p.second] + 1
          // Solo se mueven a pasto y la casilla de Mecho
          && (board[nx][ny] == 'G' || board[nx][ny] == 'M')
        ) {
          dist_to_bees[nx][ny] =
          dist_to_bees[p.first][p.second] + 1;
          bees.emplace_back(nx, ny);
        }
      }
    }
  }
}

// Dado un segundo t, verificar si saliendo en ese segundo
// se puede llegar sano y salvo a la casa
bool test(int t) {
  // Si en ese segundo ya hay abejas en la casilla de Mecho, muere
  if(dist_to_bees[mecho.first][mecho.second] <= t) return false;

  auto visited = vector<vector<bool>>(n, vector<bool>(n, false));
  visited[mecho.first][mecho.second] = true;

  // Hacemos bfs, y guardamos para cada casilla activa la cantidad
  // de pasos que pasaron desde la inicial. notese que hay S pasos
  // en un minuto, por lo que si una casilla está a (i) pasos de la
  // original, lo estará en el minuto (i / s + t), y hay que verifica
  // que en ese momento no haya abejas (o lo que es lo mismo, que
  // la distancia a los panales sea mayor a eso)
  deque<pair<int, pair<int, int>>> mechos = {{0, mecho}};
  while(!mechos.empty()) {
    auto p = mechos.front();
    auto m = p.second;
    auto i = p.first;
    if(board[m.first][m.second] == 'D') return true; // Llegamos
    mechos.pop_front();
    for(auto d : dirs) {
      int nx = m.first + d.first;
      int ny = m.second + d.second;
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if(!visited[nx][ny] && (i + 1) / s + t < dist_to_bees[nx][ny] && board[nx][ny] != 'T') {
          mechos.emplace_back(i + 1, make_pair(nx, ny)); 
          visited[nx][ny] = true;
        }
      }
    }
  }

  return false;
}

void testcase() {
  cin >> n >> s;
  board = vector<vector<char>>();
  forn(i, n) {
    board.emplace_back();
    forn(j, n) {
      board.back().emplace_back();
      cin >> board.back().back();
      if(board.back().back() == 'M') mecho = {i, j};
    }
  }

  calc_dist_to_bees();

  // Es claro que si no se puede llegar habiendo salido
  // en un tiempo t, tampoco se podrá en t + 1
  // Por eso así nos fijamos si se puede
  if(!test(0)) {
    cout << -1 << endl;
    return;
  }

  // Además por eso tambien podemos hacer busqueda binaria

  // Probamos t's hasta que ya no pueda, multiplicando
  // por 2 por la complejidad
  int t = 1;
  while(test(t)) t *= 2;

  // Bisqueda binaria
  int lo = 0;
  int hi = t;
  while(lo != hi - 1) {
    int mid = hi + lo;
    mid /= 2;
    if(test(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
}

int main() {
  int T;
  cin >> T;
  forn(i, T) testcase();
}
