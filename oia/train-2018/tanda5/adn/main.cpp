#include <bits/stdc++.h>
using namespace std;

const int INF = 333333;

#define cin ifs
#define cout ofs


int main() {
  ifstream ifs("adn.in");
  ofstream ofs("adn.out");
  int n(0), m(0), k(0);
  cin >> n >> m >> k;

  string ns, ms;
  cin >> ns >> ms;

  if(n > m) {
    swap(n, m);
    swap(ns, ms);
  }

  if(m - n > k) {
    cout << "Muy distintas." << endl;
    return 0;
  }

  // Es el algoritmo estándar de edit_distance,
  // solo observando los elementos k por encima y k por debajo
  // de la diagonal principal de la matriz dp, ya que el resto de los
  // elementos compara strigs de diferencia de longitud myor a k, entonces
  // su edit distance es necesariamente mayor a k, y no nos importa

  int size = 2 * k + 1;

  // Para hacer dp, nesecesitamos el valor anterior de la sección de la
  // columna que estábamos mirando, así como otro vector para ir guar-
  // dando lo que calculamos en la columna actual
  // Estos dos vectores son a y b, en algun orden. Los vamos cambiando
  vector<int> a(size, INF);
  vector<int> b(size, INF);
  
  vector<int> * dp = &a;
  vector<int> * new_dp = &b;

  // El caso base
  for(int i = 0; i <= k; ++i) {
    (*dp)[k + i] = i;
  }

  for(int x = 0; x < n; ++x) {
    // dp[k] represents edit_distance(ns[:x], ms[:x])
    // dp[i] represents edit_distance(ns[:x-k+i], ms[:x])
    for(int i = 0; i < size; ++i) {
      // We're looking at entry (x, i - k + x)
      int add_n;
      if(i + 1 < 0 || i + 1 >= size) {
        add_n = INF;
      } else {
        add_n = (*dp)[i + 1] + 1;
      }

      int add_m;
      if(i - 1 < 0 || i - 1 >= size) {
        add_m = INF;
      } else {
        add_m = (*new_dp)[i - 1] + 1;
      }

      int mod;
      if(i >= size || i < 0 || x >= n || x < 0 || i + x - k >= m || i + x - k < 0) {
        mod = INF;
      } else { 
        mod = (*dp)[i] + ((ns[x] == ms[i + x - k]) ? 0 : 1);
      }

      // Cansideramos las 3 posibilidades de la recirsión,
      // añadir una letra, quitar una letra, o modificar una letra
      // (dejarla igual cuenta como modificarla, pero cuesta 0)

      (*new_dp)[i] = min(mod, min(add_n, add_m));
    }

    // cambiamos a y b de lugar
    auto tmp = dp;
    dp = new_dp;
    new_dp = tmp;
  }

  if((*dp)[m - n + k] > k) {
    cout << "Muy distintas." << endl;
  } else {
    cout << (*dp)[m - n + k] << endl;
  }
}
