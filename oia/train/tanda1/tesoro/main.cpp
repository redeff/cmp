#include <bits/stdc++.h>
using namespace std;

struct Tile {
  int x;
  int y;
  Tile(int x, int y): x(x), y(y) {}
  Tile operator+(Tile t) {
    return Tile(x + t.x, y + t.y);
  }
  Tile(){}
  bool operator==(const Tile t) const {
    return x == t.x && y == t.y;
  }
};

struct State {
  Tile t;
  int len;
  int arrows;

  bool better(State s) {
    return arrows > s.arrows;
  }
  State(Tile t, int len, int arrows): t(t), len(len), arrows(arrows) {}
  State(){}

  bool operator==(const State s) const {
    return t == s.t && len == s.len && arrows == s.arrows;
  }
};

struct StateHash {
  size_t operator () (const State & s) const {
    auto h0 = hash<int>{}(s.t.x);
    auto h1 = hash<int>{}(s.t.y);
    auto h2 = hash<int>{}(s.len);
    auto h3 = hash<int>{}(s.arrows);
    return h0 ^ h1 ^ h2 ^ h3;
  } 
};

vector<Tile> nei = {Tile(0, 1), Tile(0, -1), Tile(1, 0), Tile(-1, 0)};

bool in_bound(int n, int x) {
  return x >= 0 && x < n;
}

/*#define ifs cin
#define ofs cout*/
/*
#define DBG(x) cerr << "(" << __LINE__ << ") " << #x << " = " << (x) << endl
#define RAYA cerr << "=========================" << endl
*/
#define DBG(x)
#define RAYA

int main() {
  unordered_map<State, State, StateHash> from;

  ifstream ifs;
  ifs.open("tesoro.in");
  ofstream ofs;
  ofs.open("tesoro.out");

  int n, m, f;
  ifs >> m >> n >> f;
  vector<vector<char>> board(n, vector<char>(m));
  for(int y = 0; y < m; ++y) {
    for(int x = 0; x < n; ++x) {
      ifs >> board[x][y];
    }
  }

  for(int y = 0; y < m ; ++y) {
    for(int x = 0; x < n; ++x) {
      DBG(x);
      DBG(y);
      DBG(board[x][y]);
      RAYA;
    }
  }

  vector<State> curr;
  curr.emplace_back(Tile(0, 0), 0, f);
  vector<vector<State>> bests(n, vector<State>(m, State(Tile(0, 0), 33333333, -1))); 
  bests[0][0] = State(Tile(0, 0), 0, f);

  State win_state;
  vector<State> ncurr;

  while(!curr.empty()) {
    for(State s : curr) {
      DBG(s.t.x);
      DBG(s.t.y);
      RAYA;
      for(Tile ne : nei) {
        Tile new_pos = ne + s.t;
        if(in_bound(n, new_pos.x) && in_bound(m, new_pos.y)) {
          char this_tile = board[new_pos.x][new_pos.y];
          if(this_tile != 'P') {
            int arrows = ((this_tile == 'W') ? (s.arrows - 1) : (s.arrows));
            // cerr << "parent: " << endl;
            DBG(s.t.x);
            DBG(s.t.y);
            DBG(arrows);
            DBG(new_pos.x);
            DBG(new_pos.y);
            State ns = State(new_pos, s.len + 1, arrows);
            if(ns.better(bests[new_pos.x][new_pos.y])) {
              bests[new_pos.x][new_pos.y] = ns;
              from[ns] = s;
              if(this_tile == 'T') {
                win_state = ns;
                goto out;
              }
              ncurr.push_back(ns);
              DBG(ns.t.x);
              DBG(ns.t.y);
              RAYA;
            }
          } else {
            DBG(new_pos.x);
            DBG(new_pos.y);
            DBG(this_tile);
          }
        } else {
          DBG(new_pos.x);
          DBG(new_pos.y);
          RAYA;
        }
      }
    }

    swap(ncurr, curr);
    ncurr.clear();
  }
  ofs << "imposible" << endl;
  return 0;

out:
  ;

  vector<State> way;
  while(true) {
    way.push_back(win_state);
    win_state = from[win_state];
    if(win_state.t.x == 0 && win_state.t.y == 0) break;
  }
  ofs << way.size() + 1 << endl;
  ofs << "(0,0)" << endl;
  for(int i = way.size() - 1; i >= 0; --i) {
    ofs << "(" << way[i].t.y << "," << way[i].t.x << ")" << endl;
  }

}

// Store letters in 2d array BOARD
// Have an array of the "best" state for each cell 
// (the one that still holds the most arrows)
// Have a tree (map<State, State>) to find the 
// Way once we're done
// En each BFS iteration we're given a state, we should:
//   * Check every neighbour
//   * See if it loses arrows (due to monsters)
//   * See if the new state is better than the previous
//   one in that position; it is, update accordingly,
//   else drop this new state
//   * Update the state tree
//   REPEAT
