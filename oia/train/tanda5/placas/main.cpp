#include <bits/stdc++.h>
using namespace std;

// Esta es una solución O(n^5). Vamos a demostrar que funciona
//
// Sea R el cerco rectangular max chico que aisla todo el material
// radioactivo. Y sea S la región que rodea casa desecho radioactivo
// con perímetro óptimo (lo que nos pide el problema)
//
// Supongamos que toda columna en R y toda fila en R tienen al menos
// una casilla en S. Luego, suponé que caminamos desde arriba de una columna
// hacia abajo, entonces en algún momento entramos a un predio radioactivo,
// y luego salimos de él, por lo que atravezamos 2 placas horizontales.
// Lo mismo con cada fila pero atravezamos placas verticales.
// Entonces, a cada columna y fila le corresponden dos placas distintas,
// entonces hay almenos 2(C + F) placas, donde C es el numero de columnas de R
// y F es el número de filas de R, pero esta es la fórmula de perímetro,
// entonces encerras a todo lo radioactivo con un solo rectángulo y ocupas
// a lo sumo la misma cantidad de placas que con S, que era óptimo, entonces
// R es óptimo, entonces hacemos eso
//
// Si la hipótesis es falsa, entonces existe una columna o fila (wlog columna)
// que no pasa por nunguna casilla de S, por lo que, 
// si partimos la configuración en dos partes por esa columna, tenemos dos
// configuraciones independientes, resolvemos el problema para esas configura_
// ciones, y sumamos los resultados.
//
// Con dinámica podemos guardar los resultados para cada uno de los O(n^4),
// y luego la recursión es O(n) (hay que fijarse cada fila y cada columna)
//
// Para caracterizar estos rectángulos haremos un tablero imaginario,
// donde de n x n, donde cada pedazo radioactivo está en una casilla,
// esto es facil hacer si ordenamos los pedazos radioactivos por su coordenada
// x e y, y las divisiones del tablero serán divisiones entre elementos
// consecutivos en cada uno de esos ordenamientos
//
// Tablero imaginario
//
// +-----+---+-------+-----------+----+
// |     |   |       |           |    |
// |   · |   |       |           |    |
// +-----+---+-------+-----------+----+
// |     |·  |       |           |    |
// +-----+---+-------+-----------+----+
// |     |   |    ·  |           |    |
// |     |   |       |           |    |
// |     |   |       |           |    |
// +-----+---+-------+-----------+----+
// |     |   |       |           | ·  |
// +-----+---+-------+-----------+----+
// |     |   |       |           |    |
// |     |   |       |           |    |
// |     |   |       | ·         |    |
// +-----+---+-------+-----------+----+
//
// · = pedazo radioactivo

const int INF = 33333333;
// Ancho, Alto, x, y
// dp[ancho][alto][x][y] representa el resultado para el rectángulo con una
// esquina en la posición x,y del tablero y ancho ancho y alto alto
// (en casillas del tablero)
vector<vector<vector<vector<int>>>> dp;

// Los ordenamientos de los pedazos toxicos por x y por y
vector<pair<int, int>> by_x;
vector<pair<int, int>> by_y;

#define cin ifs
#define cout ofs
int main() {
  ifstream ifs("placas.in");
  ofstream ofs("placas.out");

  int k, n;

  cin >> k >> n;

  for(int i = 0; i < n; ++i) {
    by_x.emplace_back();
    cin >> by_x.back().first;
    cin >> by_x.back().second;
  }

  by_y = by_x;

  sort(by_x.begin(), by_x.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });
  sort(by_y.begin(), by_y.end(), [](pair<int, int> a, pair<int, int> b) { return a.second<b.second; });

  // Este emplace_back es para comenzar los anchos en 1 y no en 0
  dp.emplace_back();
  for(int w = 1; w <= n; ++w) {

    // Este emplace_back es para comenzar los altos en 1 y no en 0
    dp.emplace_back();

    dp.back().emplace_back();
    for(int h = 1; h <= n; ++h) {
      dp.back().emplace_back();
      for(int x = 0; x < n - w + 1; ++x) {
        dp.back().back().emplace_back();
        for(int y = 0; y < n - h + 1; ++y) {
          dp.back().back().back().emplace_back();

          // Acá tenemos un loop sobre todos los anchos, altos, y x e y.

          // Estos cuatro condicionales detectan si hay alguna fila o columna vacía en
          // el borde de nuestro subtablero (el de este ancho, alto, x e y), y si la hay,
          // toman el valor en dp del subtablero sin esa columna/fila y lo utilizan
          if(by_x[x].second < by_y[y].second || by_x[x].second > by_y[y + h - 1].second) {
            dp[w][h][x][y] = (w == 1) ? 0 : dp[w - 1][h][x + 1][y];
            // cerr << "1F ";
          } else if(by_x[x + w - 1].second < by_y[y].second || by_x[x + w - 1].second > by_y[y + h - 1].second) {
            dp[w][h][x][y] = (w == 1) ? 0 : dp[w - 1][h][x][y];
            // cerr << "2F ";
          } else if(by_y[y].first < by_x[x].first || by_y[y].first > by_x[x + w - 1].first) {
            dp[w][h][x][y] = (h == 1) ? 0 : dp[w][h - 1][x][y + 1];
            // cerr << "3F ";
          } else if(by_y[y + h - 1].first < by_x[x].first || by_y[y + h - 1].first > by_x[x + w - 1].first) {
            dp[w][h][x][y] = (h == 1) ? 0 : dp[w][h - 1][x][y];
            // cerr << "4F ";
          } else {
            // Si ninguna de las columnas ni filas extremo están vacías, procedemos a la recursión,
            // iteramos por todas las columnas y filas que nos parte al tablero en 2 (siempre hablamos
            // de nuestro tablero imaginario) y vamos la suma de los resultados de esos subtableros

            // Primero best es el perímetro de encerrar todo con un rectángulo
            int best = 0;
            best += 2 * (by_x[x + w - 1].first - by_x[x].first);
            best += 2 * (by_y[y + h - 1].second - by_y[y].second);
            best += 8 * k;
            // cout << best << " : ";

            // por cada columna
            for(int d = 1; d < w; ++d) {
              best = min(best, dp[d][h][x][y] + dp[w - d][h][x + d][y]);
            }

            // por cada fila
            for(int d = 1; d < h; ++d) {
              best = min(best, dp[w][d][x][y] + dp[w][h - d][x][y + d]);
            }

            dp[w][h][x][y] = best;
          }
        }
      }
    }
  }

  cout << dp[n][n][0][0] << endl;
}
