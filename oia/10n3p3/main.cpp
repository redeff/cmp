#include <bits/stdc++.h>
using namespace std;

#define cout out
#define cin ini

int main(){
  ofstream out;
  out.open("tabiques.out");
  ifstream ini;
  ini.open("tabiques.in");
  int a, b;
  cin >> a >> b;
  vector<vector<unsigned int>> grid(a, vector<unsigned int>(b));

  const unsigned int UP = (1 << 0);
  const unsigned int DOWN = (1 << 1);
  const unsigned int RIGHT = (1 << 2);
  const unsigned int LEFT = (1 << 3);
  unsigned int dirs[4] = {UP, DOWN, LEFT, RIGHT};
  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {1, -1, 0, 0};
  const unsigned int VISITED = (1 << 4);

  int t;
  cin >> t;

  //cout << "LALA " << t << endl;
  for(int i = 0; i < t + 4; ++i){
    //cout << "LULA" << endl;
    int x1, y1, x2, y2;
    if(i < t){
      cin >> x1 >> y1 >> x2 >> y2;
    } else {
      switch(i - t){
        case 0:
          x1 = 0; x2 = 0; y1 = 0; y2 = b;
          break;
        case 1:
          x1 = a; x2 = a; y1 = 0; y2 = b;
          break;
        case 2:
          x1 = 0; x2 = a; y1 = b; y2 = b;
          break;
        case 3:
          x1 = 0; x2 = a; y1 = 0; y2 = b;
          break;
      }
      //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
      //cout << i - t << endl;
    }
    //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    if(x1 != x2){
      if(x1 > x2){
        swap(x1, x2);
        swap(y1, y2);
      }
      for(int i = x1; i < x2; ++i){ 
        if(y1 < b) grid[i][y1] |= DOWN;
        if(y1 > 0) grid[i][y1 - 1] |= UP;
      }
    } else {
      if(y1 > y2){
        swap(x1, x2);
        swap(y1, y2);
      }
      for(int i = y1; i < y2; ++i){ 
        if(x1 < b) grid[x1][i] |= LEFT;
        if(x1 > 0) grid[x1 - 1][i] |= RIGHT;
      }
    }
  }
  //cout << "LALA" << endl;

  for(auto &v: grid){
    for(int i: v){
      //cout << i << " ";
    }
    //cout << endl;
  }

  vector<pair<int, int>> v;
  vector<pair<int, int>> new_v;
  v.emplace_back(0, 0);
  grid[0][0] |= VISITED;

  int num_iter = 0;
  while(!v.empty()){
    new_v.clear();
    for(pair<int, int> p: v){
      //cout << "ITER";
      int x = p.first;
      int y = p.second;
      if(x == a - 1 && y == b - 1){
        cout << num_iter;


        return 0;
      }
      for(int i = 0; i < 4; ++i){
        if(0 == (dirs[i] & grid[x][y])){
          //cout << "JAJA" << endl;
          int new_x = x + dx[i];
          int new_y = y + dy[i];
          //cout << new_x << " " << new_y << endl;
          if(0 == (grid[new_x][new_y] & VISITED)){
            //cout << "JUJA" << endl;
            grid[new_x][new_y] |= VISITED;
            new_v.emplace_back(new_x, new_y);
          } else {
            //cout << grid[new_x][new_y]<< endl;
          }
        }
      }
    }
    num_iter++;
    swap(new_v, v);
  }
  cout << "imposible" << endl;

  /*for(auto &v: grid){
    for(int i: v){
      cout << i << " ";
    }
    cout << endl;
  }*/


}

    
