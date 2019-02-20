#include <bits/stdc++.h>
using namespace std;

// Una posicion en el keyboard
struct Pos {
  int x;
  int y;
  Pos(int x, int y): x(x), y(y) {}
};

Pos operator+(Pos a, Pos b) {
  return Pos(a.x + b.x, a.y + b.y);
}

bool in_bounds(int x, int n) {
  return x >= 0 && x < n;
}

int calc() {
  // Cada una de las direcciones cardinales
  vector<Pos> neis = {Pos(1, 0), Pos(0, 1), Pos(-1, 0), Pos(0, -1)};

  int r, c;
  if(cin >> r) {
  } else {
    return -1;
  }
  cin >> c;
  vector<vector<char>> keys(c, vector<char>(r));
  for(int y = 0; y < r; ++y) {
    for(int x = 0; x < c; ++x) {
      cin >> keys[x][y];
    }
  }

  string s;
  cin >> s;
  s.push_back('*');

  // Por cada posición, cual es la máxima cantidad de letras
  // de la palabra que queremos formar que podemos haber 
  // apretado (en cada iteración)
  vector<vector<int>> max_match(c, vector<int>(r, -333333333));
  max_match[0][0] = 0;

  // BFS
  vector<pair<Pos, int>> currs{{Pos(0, 0), 0}};
  int cycles = 0;
  while(!currs.empty()) {
    cycles++;
    vector<pair<Pos, int>> n_currs;
    for(auto curr: currs) {
      // Si ya apretamos las necesarias
      if(curr.second == s.size()) {
        return cycles - 1;
      }

      // Por cada dirección cardinal
      for(auto nei: neis) {
        Pos n_pos = curr.first;
        // Hasta salirse de la tecla o salirse del tablero, le sumamos la posición cardinal
        while(in_bounds(n_pos.x, c) && in_bounds(n_pos.y, r) && keys[n_pos.x][n_pos.y] == keys[curr.first.x][curr.first.y]) {
          n_pos = n_pos + nei;
        }

        // Si terminó adentro del tablero, y la posición a la que llegamos tenia una
        // cantidad máxima de letras correctas menor a la nuestra
        if(in_bounds(n_pos.x, c) && in_bounds(n_pos.y, r) && max_match[n_pos.x][n_pos.y] < curr.second) {
          n_currs.emplace_back(n_pos, curr.second);
          max_match[n_pos.x][n_pos.y] = curr.second;
        }
      }

      // Si estamos en la tecla que tenemos que apretar
      if(keys[curr.first.x][curr.first.y] == s[curr.second]) {
        n_currs.emplace_back(curr.first, curr.second + 1);
        max_match[curr.first.x][curr.first.y] = curr.second + 1;
      }
    }

    swap(currs, n_currs);
  }
  return -1;
}

int main() {
  while(!cin.eof()) {
    int c = calc();
    if(c != -1)
      cout << c << endl;
  }
}
