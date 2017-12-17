#include <bits/stdc++.h>
using namespace std;

struct Pos {
  int x;
  int y;
  Pos(int x, int y): x(x), y(y) {}
};

Pos operator+(Pos a, Pos b) {
  return Pos(a.x + b.x, a.y + b.y);
}

bool in_bounds(int x, int n) {
  return x >= 0 && x < n;
}

//int calc(int a, int c, vector<vector<char>> keys, string s) {
int calc() {
  vector<Pos> neis = {Pos(1, 0), Pos(0, 1), Pos(-1, 0), Pos(0, -1)};

  int r, c;
  if(cin >> r) {
  } else {
    return -1;
  }
  cin >> c;
  vector<vector<char>> keys(c, vector<char>(r));
  for(int y = 0; y < r; ++y) {
    for(int x = 0; x < c; ++x) {
      cin >> keys[x][y];
    }
    //char nline;
    //cin >> nline;
  }

  string s;
  cin >> s;
  s.push_back('*');

  vector<vector<int>> max_match(c, vector<int>(r, -333333333));
  max_match[0][0] = 0;

  vector<pair<Pos, int>> currs{{Pos(0, 0), 0}};
  int cycles = 0;
  while(!currs.empty()) {
    cycles++;
    vector<pair<Pos, int>> n_currs;
    for(auto curr: currs) {
      if(curr.second == s.size()) {
        return cycles - 1;
      }

      for(auto nei: neis) {
        Pos n_pos = curr.first;
        while(in_bounds(n_pos.x, c) && in_bounds(n_pos.y, r) && keys[n_pos.x][n_pos.y] == keys[curr.first.x][curr.first.y]) {
          // if(max_match[n_pos.x][n_pos.y] < curr.second) {
          //  n_currs.emplace_back(n_pos, curr.second);
          //  max_match[n_pos.x][n_pos.y] = curr.second;
          // }
          n_pos = n_pos + nei;
        }
        if(in_bounds(n_pos.x, c) && in_bounds(n_pos.y, r) && max_match[n_pos.x][n_pos.y] < curr.second) {
          n_currs.emplace_back(n_pos, curr.second);
          max_match[n_pos.x][n_pos.y] = curr.second;
        }
      }

      if(keys[curr.first.x][curr.first.y] == s[curr.second]) {
        n_currs.emplace_back(curr.first, curr.second + 1);
        max_match[curr.first.x][curr.first.y] = curr.second + 1;
      }
    }

    swap(currs, n_currs);
  }
  return -1;
}

int main() {
  while(!cin.eof()) {
    int c = calc();
    if(c != -1)
      cout << c << endl;
  }
}
