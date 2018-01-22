#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll n;

// Wrapper para la interacción
bool get_at(pair<ll, ll> p) {
  ll x = p.first;
  ll y = p.second;
  if(x < 0 || x >= n || y < 0 || y >= n) return false;
  cout << "examine " << (x + 1) << " " << (y + 1) << endl;
  string is_flattened;
  cin >> is_flattened;
  return is_flattened == "true";
}

// Up, right, down, left
vector<pair<ll, ll>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Estas 4 funciones son para hacer busqueda binaria en vectores
pair<ll, ll> add(pair<ll, ll> a, pair<ll, ll> b) {
  return {a.first + b.first, a.second + b.second};
}

pair<ll, ll> half(pair<ll, ll> a) {
  return {a.first / 2, a.second / 2};
}

pair<ll, ll> times(pair<ll, ll> a, ll t) {
  return {a.first * t, a.second * t};
}

// Para terminar la busqueda binaria cuando las dos bounds estan cerca
bool near(pair<ll, ll> a, pair<ll, ll> b) {
  return abs(a.first - b.first) < 2 && abs(a.second - b.second) < 2;
}

int main() {
  ll x0, y0;
  cin >> n >> x0 >> y0;
  x0--; // Los pasamos a 0-indexed
  y0--;
  pair<ll, ll> init = {x0, y0};

  // bounds va a contener 4 casillas, una en cada
  // lado del cuadrado en el que nos encontramos
  vector<pair<ll, ll>> bounds;
  for(auto d : dirs) {
    // Hacemos busqueda binaria en una dirección para saber
    // donde está el borde del cuadrado.
    // Notemos que no puede interferir el siguiente cuadrado
    // porque como multilicamos por 2 siempre, antes de llegar a un
    // cuadrado vecino aplanado llegamos a una casilla no aplanada 
    auto hi = d;
    while(get_at(add(init, hi))) {
      hi = times(hi, 2);
    }
    pair<ll, ll> lo = {0, 0};
    while(!near(hi, lo)) {
      auto mid = half(add(hi, lo));
      if(get_at(add(init, mid))) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    bounds.push_back(add(lo, init));
  }

  // m es el tamaño del cuadrado. Es facil de calcular teniendo bounds
  ll m = bounds[0].second - bounds[2].second + 1;

  // calculamos el centro del cuadrado dado un punto en cada lado
  pair<ll, ll> center = {(bounds[1].first + bounds[3].first) / 2, (bounds[0].second + bounds[2].second) / 2};


  // Ahora que sabemos m podemos buscar los otros cuadrados,
  // entonces bounds contendrá los centros de los cuadrados
  // mas alto y mas bajo en la columna en la que estamos, 
  // y tambien los de los que están mas a la derecha e
  // izquierda en nuestra fila
  bounds = {};
  for(auto d : dirs) {
    auto hi = times(d, 2 * m);
    while(get_at(add(center, hi))) { // Probamos centros hasta que no esté aplanado
      hi = add(hi, times(d, 2 * m));
    }
    bounds.push_back(add(center, add(hi, times(d, -2 * m))));
  }

  // Usamos la misma formula que antes para calcular el centro esta vez de toda la figura
  center = {(bounds[1].first + bounds[3].first) / 2, (bounds[0].second + bounds[2].second) / 2};
  cout << "solution " << center.first + 1 << " " << center.second + 1 << endl;
}
