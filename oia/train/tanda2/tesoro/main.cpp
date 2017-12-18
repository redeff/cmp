#include <bits/stdc++.h>
using namespace std;

// Una posición en el BFS 3d, las posiciones (x, y) en el tablero,
// y la z representa la cantidad de flechas que me queda
struct Tile {
  int x;
  int y;
  int z;
  Tile(int nx, int ny, int nz): x(nx), y(ny), z(nz) {}
};

vector<Tile> neis = {Tile(0, 1, 0), Tile(0, -1, 0), Tile(1, 0, 0), Tile(-1, 0, 0)};

bool in_bound(int n, int x) {
  return x >= 0 && x < n;
}

int main() {
  ifstream ifs;
  ifs.open("tesoro.in");
  ofstream ofs;
  ofs.open("tesoro.out");

  int n, m, f;
  ifs >> m >> n >> f;
  vector<vector<char>> board(n, vector<char>(m));
  for(int y = 0; y < m; ++y) {
    for(int x = 0; x < n; ++x) {
      ifs >> board[x][y];
    }
  }

  // Cuál es la posición previa a cada otra. Es para poder ir para atrás al
  // final al decir el camino
  vector<vector<vector<Tile>>> from(n, vector<vector<Tile>>(m, vector<Tile>(f + 1, Tile(-1, -1, -1))));

  // En cada iteración, cual es la máxima cantidad de flechas con la que conseguimos
  // llegar a cada posición del tablero
  vector<vector<int>> max_flechas(n, vector<int>(m, -1));

  from[0][0][0] = Tile(-1, 0, f);

  // BFS
  vector<Tile> currs;

  // Ponemos la posición inicial uno afuera del tablero, cosa
  // que el BFS tenga que "entrar" al tablero y se fije si
  // la posición inicial en sí es un pozo o un mounstro
  currs.push_back(Tile(-1, 0, f));

  // Esto es para setearlo quendo encontramos el tesoro
  Tile final_pos = Tile(-1, -1, -1);
  while(!currs.empty()) {
    vector<Tile> ncurrs;
    for(Tile curr: currs) {
      for(Tile nei : neis) {
        Tile n_pos = Tile(curr.x + nei.x, curr.y + nei.y, curr.z);
        if(in_bound(n, n_pos.x) && in_bound(m, n_pos.y)) {
          char what = board[n_pos.x][n_pos.y];
          // Si es 'P' no hacemos nada
          if(what != 'P') {
            if(what == 'T') {
              // Tenemos que decirle de donde vinimos
              from[n_pos.x][n_pos.y][n_pos.z] = curr;
              final_pos = n_pos;
              goto found;
            } else {
              if(what == 'W') {
                // Si es un mounstro reducimos la cantidad de flechas
                n_pos.z--;
              }
              if(n_pos.z > max_flechas[n_pos.x][n_pos.y]) {
                max_flechas[n_pos.x][n_pos.y] = n_pos.z;
                ncurrs.push_back(n_pos);
                // Tenemos que decirle de donde vinimos
                from[n_pos.x][n_pos.y][n_pos.z] = curr;
              }
            }
          }
        }
      }
    }
    // move para que no se copie todo
    currs = move(ncurrs);
  }
  ofs << "imposible" << endl;
  return 0;

found:
  ;
  vector<Tile> poss;
  while(final_pos.x != -1) {
    // Vamos buscando el camino para atrás
    poss.push_back(final_pos);
    final_pos = from[final_pos.x][final_pos.y][final_pos.z];
  }
  ofs << poss.size() << endl;
  for(int i = int(poss.size()) - 1; i >= 0; --i) {
    ofs << "(" << poss[i].y << "," << poss[i].x << ")" << endl;
  }
}

// Store letters in 2d array BOARD
// Have an array of the "best" state for each cell 
// (the one that still holds the most arrows)
// Have a tree (map<State, State>) to find the 
// Way once we're done
// En each BFS iteration we're given a state, we should:
//   * Check every neighbour
//   * See if it loses arrows (due to monsters)
//   * See if the new state is better than the previous
//   one in that position; it is, update accordingly,
//   else drop this new state
//   * Update the state tree
//   REPEAT
