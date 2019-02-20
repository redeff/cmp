#include <bits/stdc++.h>
using namespace std;

struct Fecha {
    int dia, mes,anno;
};

// Compara las edades
// Esta al reves porque Fecha representa
// fecha de nacimiento y no edad
bool operator<(Fecha a, Fecha b) {
  if(a.anno < b.anno) return false;
  if(a.anno > b.anno) return true;

  if(a.mes < b.mes) return false;
  if(a.mes > b.mes) return true;

  if(a.dia < b.dia) return false;
  if(a.dia > b.dia) return true;

  return false;
}

vector<int> enojados;
vector<int> no_enojados;
vector<pair<int, int>> enojados_with_enojo;
int max_enojo = 0;

int fila(vector<Fecha> orden, vector<int> &es) {
  Fecha minima_edad;
  minima_edad.anno = -33333333;
  for(int i = 0; i < orden.size(); ++i) {
    if(minima_edad < orden[i]) {
      enojados.push_back(i);
    } else {
      minima_edad = orden[i];
      no_enojados.push_back(i);
    }
  }

  // no_enojados en orden ascendente, sus orden[i] descendente
  reverse(no_enojados.begin(), no_enojados.end());
  // no_enojados en orden descendente, sus orden[i] ascendente
  
  for(int i = 0; i < enojados.size(); ++i) {
    // Con binary search obtenemos
    // el mas joven mas cercano a la caja
    // Notemos que este claramente es no enojado,
    // y los no enojados estan ordenados,
    // lo que nos permite hacer busqueda binaria
    int index_no_enojado_menor = *(lower_bound(
      no_enojados.begin(), 
      no_enojados.end(), 
      enojados[i], 
      [&orden](int a, int b) {
        return orden[a] < orden[b];
      }
    ) - 1);
    int enojo = enojados[i] - index_no_enojado_menor;
    max_enojo = max(max_enojo, enojo);
    enojados_with_enojo.emplace_back(-enojo, enojados[i]);
  }  

  // Ordenamos como nos pide el problema
  sort(enojados_with_enojo.begin(), enojados_with_enojo.end());

  for(auto p : enojados_with_enojo) {
    es.push_back(1 + p.second);
  }

  return max_enojo;
}

