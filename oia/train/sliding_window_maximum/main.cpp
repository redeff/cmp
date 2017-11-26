#include <bits/stdc++.h>
using namespace std;

const int INF = 9999999;


bool is_local_min(int i, vector<pair<int, int>>& nei, vector<int>& ns) {
  return ns[nei[i].first] >= ns[i] && ns[nei[i].second] >= ns[i];
}

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    // (complejidad O(n) (creo))
    //
    // La idea es tomar, para cada punto en el array,
    // Sus dos "vecinos", que en principio son los vecinos
    // reales (lo que tienen indices i + 1 y i - 1),
    // pero a lo largo del algoritmo vamos eliminando
    // elementos del array, por lo que los vecinos cambian
    // (en realidad no eliminamos a ningún elemento del array,
    // solo los ignoramos)
    //
    // Luego, tomamos los "minimos locales", los puntos
    // cuyos dos vecinos son al menos tan grandes en valor
    // que el, y eliminar a estos minimos locales, preservando
    // las relaciones de vecinidad
    //
    // Por como hacemos esto, entre dos casillas "vecinas"
    // siempre habra casillas con valores menores a estas
    // vecinas, lo que nos permite, al ir eliminando casillas
    // poder determinar el maximo de cada seccion pudiendo
    // ignorar las que sabemos que son menores

    // Agregar INF al principio y al final
    // reduce los casos borde
    if(nums.size() == 0) return {};
    vector<int> ns;
    ns.push_back(INF);
    for(int n : nums) ns.push_back(n);
    ns.push_back(INF);

    vector<int> out(nums.size() - k + 1);
    unordered_set<int> local_mins;
    vector<pair<int, int>> nei(ns.size()); // Los vecinos

    for(int i = 0; i < ns.size(); ++i) {
      nei[i].first = i - 1;
      nei[i].second = i + 1;

      if(is_local_min(i, nei, ns)) local_mins.insert(i);
    }

    while(!local_mins.empty()) {

      // Tomamos un minimo local cualquiera,
      // lo vamos a eliminar
      int l = *local_mins.begin();

      // Preservamos las telaciones de vecinidad
      // al matar a l
      nei[nei[l].first].second = nei[l].second;
      nei[nei[l].second].first = nei[l].first;

      // Aca usamos que los valores en el rango (nei[l].first, l) y (l, nei[l].second)
      // son todos menores o iguales a l
      for(int i = max(l - k + 1, nei[l].first + 1); i <= min(nei[l].second - k, l); ++i) {
        // Es i - 1 porque ns esta corrido con respecto a nums
        out[i - 1] = ns[l];
      }

      // Borramos l
      local_mins.erase(local_mins.begin());

      // Volvemos a checkear los elementos cuyos vecinos cambiaron
      for(auto n : {nei[l].first, nei[l].second}) {
        if(is_local_min(n, nei, ns)) {
          local_mins.insert(n);
          cout << "la" << endl;
        }
      }
    }

    return out;
  }

};
