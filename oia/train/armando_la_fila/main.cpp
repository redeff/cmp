#include <bits/stdc++.h>
using namespace std;

struct Fecha {
    int dia, mes,anno;
};

vector<int> ns;
vector<int> no_ens;
vector<pair<int, int>> ens;

int fila(vector<Fecha> orden, vector<int> &enojados) {
  ns.clear();
  no_ens.clear();
  ens.clear();
  for(Fecha f : orden) {
    ns.push_back(-f.dia - 32 * (f.mes + 512 * f.anno));
  }

  int mini = 999999999;

  vector<int> es;
  for(int i = 0; i < ns.size(); ++i) {
    if(mini > ns[i]) {
      no_ens.push_back(i);
      mini = ns[i];
    } else if (mini < ns[i]) {
      es.push_back(i);
    }
  }

  reverse(no_ens.begin(), no_ens.end());

  int max_e = 0;
  for(int i = 0; i < es.size(); ++i) {
    auto it = lower_bound(no_ens.begin(), no_ens.end(), i,  [](int v, int u){
      return ns[v] < ns[u];
    }) - 1;
    int e = *(it - 1);
    max_e = max(max_e, i - e);
    ens.emplace_back(e - i, i);
  }

  sort(ens.begin(),ens.end());

  for(auto p : ens) {
    enojados.push_back(1+p.second);
  }

  return max_e;
}

