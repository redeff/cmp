#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
vector<T> get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool bound(int x, int n) {
  return 0 <= x && x < n;
}

int main(){
  int n, m;
  cin >> n >> m;

  vector<string> maze(n);

  pair<int, int> start;
  for(int x = 0; x < n; ++x) {
    cin >> maze[x];
  }

  forn(x, 0, n) forn(y, 0, m) {
    if(maze[x][y] == 'S') start = {x, y};
  }

  string inst;
  cin >> inst;

  vector<int> perm(4);
  iota(perm.begin(), perm.end(), 0);


  int total = 0;
  forn(jhkjhgah, 0, 24) {
    pair<int, int> pos = start;
    for(char i : inst) {
      auto delt = dirs[perm[i - '0']];
      pos = {pos.first + delt.first, pos.second + delt.second};
      if(!bound(pos.first, n) || !bound(pos.second, m) || maze[pos.first][pos.second] == '#') goto failed;
      else if(maze[pos.first][pos.second] == 'E') goto exited;
    }
    goto failed;
exited:
    total ++;

failed:
    next_permutation(perm.begin(), perm.end());
  }

  cout << total << endl;
}

