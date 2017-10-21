#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

int main(){
  ll a, b;
  cin >> a >> b;
  vector<vector<ll>> grid;
  forn(i, 0, a){
    grid.emplace_back();
    forn(j, 0, b){
      ll tmp;
      cin >> tmp;
      grid.back().push_back(tmp);
    }
  }
  bool works = true;
  forn(i, 0, grid.size()){
    forn(j, 0, grid[0].size()){
      works = works && grid[0][0] - grid[i][0] == grid[0][j] - grid[i][j];
    }
  }
  if(!works){
    cout << "-1" << endl;
    return 0;
  }
  //grid's a*b
  ll minx = grid[0][0];
  ll minix = 0;
  ll sumx = 0;
  forn(i, 0, grid.size()){
    if(minx > grid[i][0]){
      minx = grid[i][0];
      minix = i;
    }
    sumx += grid[i][0];
  }
  sumx -= minx * grid.size();

  ll miny = grid[0][0];
  ll miniy = 0;
  ll sumy = 0;
  forn(i, 0, grid[0].size()){
    if(miny > grid[0][i]){
      miny = grid[0][i];
      miniy = i;
    }
    sumy += grid[0][i];
  }
  sumy -= miny * grid[0].size();

  ll mina = grid[minix][miniy];
  ll total = mina * min(grid.size(), grid[0].size());
  total += sumx + sumy;
  cout << total << endl;
  forn(i, 0, min(grid.size(), grid[0].size())){
    forn(j, 0, mina)
      cout << (grid.size() < grid[0].size() ? "row " : "col ") << i + 1 << endl;
  }
  forn(i, 0, grid.size()){
    forn(j, 0, grid[i][miniy] - mina){
      cout << "row " << i + 1 << endl;
    }
  }
  forn(i, 0, grid[0].size()){
    forn(j, 0, grid[minix][i] - mina){
      cout << "col " << i + 1 << endl;
    }
  }
}
