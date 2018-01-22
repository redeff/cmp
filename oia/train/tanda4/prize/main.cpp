#include "prize.h"
#include <bits/stdc++.h>
using namespace std;

int n;

// Identificamos el "rank" de cada elemento por
// la suma de los dos elemetos en ask(ese elemento),
// es decir, la cantidad con tipo menor a el.
// curr_max es el mayor de estos ranks que encontramos
// hasta ahora
// Notemos que hay a lo sumo sqrt(n) elementos con
// rank menor a curr_max en todo momento (sqrt(n) ~ 500)
int curr_max = -1;

// Buffereamos los asks para no preguntar dos veces por lo mismo
vector<pair<int, int>> buffer;

// Buffered ask()
pair<int, int> get_at(int t) {
  if(t == -1) {
    for(int i = 0; i < n; ++i) {
      if(buffer[i] == make_pair(0, 0)) return {i, i};
    }
    return {-1, -1};
  }
  if(buffer[t].first == -1) {
    vector<int> res = ask(t);
    buffer[t].first = res[0];
    buffer[t].second = res[1];
    return buffer[t];
  } else return buffer[t];

}

int get_rank(int t) {
  return get_at(t).first + get_at(t).second;
}

// Ejecuta ask(t) para todo t con rank menor a curr_max en [b; e]
// esto lo hace con busqueda binaria y de forma recursiva
//
// Solo funciona si todos los elementos por los que pregunta
// tienen rank <= curr_max, entonces si encuentra un elemento
// que no cumple esto, updatea curr_max, y devuelve true para
// que el caller sepa que hay que hacer todo de nuevo con el
// nuevo curr_max.
bool search_range(int b, int e) {

  // Toma el primero en [b; e] con rank mayor o igual a curr_max y lo pone en b
  while(get_rank(b) < curr_max && b <= e) b++;
  // Toma el ultimo en [b; e] con rank mayor o igual a curr_max y lo pone en e
  while(get_rank(e) < curr_max && b <= e) e--;

  // Esto pasa si todos en el rango [b; e] tenian rango menor a curr_max,
  // esto quere decit que con lo anterior ya los askeamos todos
  if(e < b) return false;

  // Nos fijamos si llegamos a un nuevo maximo
  if(max(get_rank(b), get_rank(e)) > curr_max) {
    curr_max = max(get_rank(b), get_rank(e));
    return true;
  }

  // total en la cantidad en el rango [b; e] de 
  // elementos con rank menor a curr_max
  int total = get_at(e).first - get_at(b).first;

  // si hay 0 ni nos fijamos
  if(total != 0) {
    // Aplicamos el algoritmo recursivamente.
    // si alguno de nuestros hijos encontró un nuevo maximo
    // que invalide todo lo propagamos
    if(search_range(b, (e + b) / 2)) return true;
    if(search_range((e + b) / 2, e)) return true;
  }

  return false;
}

int find_best(int nn) {
  n = nn;
  buffer = vector<pair<int, int>>(n, {-1, -1});

  // Cada vez que se invalida lo volvemos a hacer
  while(search_range(0, n - 1));

  // Entonces ahora todos los elementos en [0; n-1] con rank menor
  // a curr_max estan askeados. Esto incluye el diamante. Entonces
  // buscamos al de rank 0
  for(int i = 0; i < n; ++i) {
    if(buffer[i] == make_pair(0, 0)) return i;
  }

  // Imposible llegar aca si el algoritmo es correcto
  return -1;
}
