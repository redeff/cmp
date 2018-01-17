#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> board;
vector<vector<int>> dist_to_bees;

#define forn(i, n) for(int i = 0; i < n; ++i)

int n;
int s;

pair<int, int> mecho;

pair<int, int> dirs[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void calc_dist_to_bees() {
  dist_to_bees = vector<vector<int>>(n, vector<int>(n, 33333333));
  deque<pair<int, int>> bees;
  forn(i, n) forn(j, n) if(board[i][j] == 'H') {
    bees.emplace_back(i, j);
    dist_to_bees[i][j] = 0;
  }

  while(!bees.empty()) {
    auto p = bees.front();
    bees.pop_front();
    for(auto d : dirs) {
      int nx = p.first + d.first;
      int ny = p.second + d.second;
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if(
          dist_to_bees[nx][ny] > 
          dist_to_bees[p.first][p.second] + 1
          && (board[nx][ny] == 'G' || board[nx][ny] == 'M')
        ) {
          dist_to_bees[nx][ny] =
          dist_to_bees[p.first][p.second] + 1;
          bees.emplace_back(nx, ny);
        }
      }
    }
  }
}

// Check if leaving at second d is soon enough
bool test(int t) {
  if(dist_to_bees[mecho.first][mecho.second] <= t) return false;

  auto visited = vector<vector<bool>>(n, vector<bool>(n, false));
  visited[mecho.first][mecho.second] = true;

  deque<pair<int, pair<int, int>>> mechos = {{0, mecho}};
  while(!mechos.empty()) {
    auto p = mechos.front();
    auto m = p.second;
    auto i = p.first;
    if(board[m.first][m.second] == 'D') return true;
    mechos.pop_front();
    for(auto d : dirs) {
      int nx = m.first + d.first;
      int ny = m.second + d.second;
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if(!visited[nx][ny] && (i + 1) / s + t < dist_to_bees[nx][ny] && board[nx][ny] != 'T') {
          mechos.emplace_back(i + 1, make_pair(nx, ny)); 
          visited[nx][ny] = true;
        }
      }
    }
  }

  return false;
}

void testcase() {
  cin >> n >> s;
  board = vector<vector<char>>();
  forn(i, n) {
    board.emplace_back();
    forn(j, n) {
      board.back().emplace_back();
      cin >> board.back().back();
      if(board.back().back() == 'M') mecho = {i, j};
    }
  }

  calc_dist_to_bees();
  if(!test(0)) {
    cout << -1 << endl;
    return;
  }

  int t = 1;
  while(test(t)) t *= 2;
  int lo = 0;
  int hi = t;
  while(lo != hi - 1) {
    int mid = hi + lo;
    mid /= 2;
    if(test(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
}

int main() {
  int T;
  cin >> T;
  forn(i, T) testcase();
}
