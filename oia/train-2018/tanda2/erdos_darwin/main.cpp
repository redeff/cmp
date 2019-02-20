#include <bits/stdc++.h>
using namespace std;

// Dada una persona del grafo, calcula para cada una de las otras
// a que distancia está de ésta
vector<int> dist(vector<vector<int>> &graph, int n, int person) {
  vector<int> out(n, 33333333);
  out[person] = 0;
  vector<int> curr{person};

  // BFS
  while(!curr.empty()) {
    vector<int> n_curr;
    for(int c : curr) {
      for(int ne : graph[c]) {
        if(out[ne] > out[c] + 1) {
          // Tiene distancia uno mayor que su vecino
          out[ne] = out[c] + 1;
          n_curr.push_back(ne);
        }
      }
    }
    swap(curr, n_curr);
  }

  return out;
}

int main() {
  int n, m;
  cin >> n >> m;
  int d;
  cin >> d;

  vector<vector<int>> graph(n);

  for(int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  // Calcula las distancias desde cada persona hasta erdos y darwin
  auto dist_erdos = dist(graph, n, 0);
  auto dist_darwin = dist(graph, n, n - 1);

  int total = 0;
  for(int i = 0; i < n; ++i) {
    if(dist_erdos[i] + dist_darwin[i] <= d) total++;
  }

  cout << total << endl;
}
