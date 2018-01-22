#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Estructura de datos que permite:
//  * Insertar un entero en el rango [0, n]
//  * Obtener el mayor `gap` entre enteros consecutivos
//  de los que insertamos si los ordenamos 
struct BiggestGap {
  // Los gaps los ordenamos por tamaño
  multiset<ll> gaps;
  set<ll> points;

  BiggestGap(ll n) {
    points = {0, n};
    gaps = {n};
  }

  ll max_gap() {
    return *gaps.rbegin();
  }

  void add_point(ll p) {
    if(points.count(p) > 0) return;
    points.insert(p);
    ll a = *prev(points.find(p));
    ll b = *next(points.find(p));
    gaps.erase(gaps.find(b - a));
    gaps.insert(p - a);
    gaps.insert(b - p);
  }
};

// El área mas grande va a consistir claramente
// en el rectángulo formado por el par de lineas verticales
// más lejanas y el par de lineas horizontales mas lejanas
// la distancia entre lineas paralelas las podemos interpretar
// como `gaps` en nuestra estructura 
void testcase() {
  ll n, m, q;
  cin >> n >> m >> q;
  auto x_gapper = BiggestGap(n);
  auto y_gapper = BiggestGap(m);
  for(ll i = 0; i < q; ++i) {
    ll c, v;
    cin >> c >> v;
    // Añadimos la linea a la estructura correspondiente
    (c == 0 ? x_gapper : y_gapper).add_point(v);
    cout << x_gapper.max_gap() * y_gapper.max_gap() << endl;
  }
}

int main() {
  ll T;
  cin >> T;
  for(ll i = 0; i < T; ++i) testcase();
}
