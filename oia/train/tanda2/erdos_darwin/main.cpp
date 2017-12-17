#include <bits/stdc++.h>
using namespace std;

vector<int> dist(vector<vector<int>> &graph, int n, int person) {
  vector<int> out(n, 33333333);
  out[person] = 0;
  vector<int> curr{person};
  while(!curr.empty()) {
    vector<int> n_curr;
    for(int c : curr) {
      for(int ne : graph[c]) {
        if(out[ne] > out[c] + 1) {
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
  auto dist_erdos = dist(graph, n, 0);
  auto dist_darwin = dist(graph, n, n - 1);

  int total = 0;
  for(int i = 0; i < n; ++i) {
    if(dist_erdos[i] + dist_darwin[i] <= d) total++;
  }

  cout << total << endl;
}
