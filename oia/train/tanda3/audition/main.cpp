#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void testcase() {
  ll n, k;
  cin >> n >> k;
  if(k != 0) {
    // with_n_boys_before[u] contiene la cantidad de personas en la fila
    // con exactamente u hombres atrás de ellos, incluyendo una "persona fantasma"
    // al final de todos
    vector<ll> with_n_boys_before = {1};
    for(ll i = 0; i < n; ++i) {
      char c;
      cin >> c;
      if(c == '1') {
        with_n_boys_before.push_back(1);
      } else {
        with_n_boys_before.back()++;
      }
    }

    ll total = 0;
    for(ll i = 0; i < ll(with_n_boys_before.size()) - k; ++i) {
      // para que el rango (i, j) funcione, si la i-ésima persona
      // tiene u hombres detrás, la j+1-ésima deverá tener u + k
      // Entonces elegir pares es euivalente a elegir pares de cada uno
      // de los conjuntos with_n_boys_before[i] y with_n_boys_before[i + k] para todo i
      total += with_n_boys_before[i] * with_n_boys_before[i + k];
    }
    cout << total << endl;
  } else {
    // Grupos de chicas consecutivos
    vector<ll> groups;
    string s;
    cin >> s;
    for(ll i = 0; i < ll(s.size()); ++i) {
      if(s[i] == '0') {
        if(i == 0 || s[i - 1] == '1') groups.push_back(1);
        else groups.back()++;
      }
    }
    ll total = 0;
    // hay (g * (g - 1)) / 2 + g formas de elegir pares en un
    // grupo de g cosas
    for(auto g : groups) total += (g * (g - 1)) / 2 + g;
    cout << total << endl;
  }
}

int main() {
  int T;
  cin >> T;
  for(int i = 0; i < T; ++i) testcase();
}
