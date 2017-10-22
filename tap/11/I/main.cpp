#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> conn;

pair<int, int> deepest(int curr, int from){
  pair<int, int> maxi = {curr, 0};
  for(auto i : conn[curr]){
    if(i != from){
      auto rec = deepest(i, curr);
      if(rec.second + 1 > maxi.second){
        maxi = make_pair(rec.first, rec.second + 1);
      }
    }
  }
  return maxi;
}

int main(){
  while(true){
    int n;
    cin >> n;
    if(n == -1) break;
    conn.clear();
    conn.resize(n);
    for(int i = 1; i < n; ++i){
      int tmp;
      cin >> tmp;
      tmp--;
      conn[i].push_back(tmp);
      conn[tmp].push_back(i);
    }

    auto dep = deepest(0, -1);
    dep = deepest(dep.first, -1);
    cout << ((dep.second + 1) / 2) << endl;
  }
}
  
