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

struct Node {
  vector<int> chs;
  int deps;
  bool col;
  Node(vector<int> chs, int deps, bool col): chs(chs), deps(deps), col(col) {}
  Node(): deps(0) {}
};

int main(){
  int n;
  int m;
  cin >> n >> m;
  vector<Node> ns(n);
  for(int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp;
    ns[i].col = tmp == 0;
    ns[i].deps = 0;
  }

  for(int i = 0; i < m; ++i) {
    int t1, t2;
    cin >> t1 >> t2;
    ns[t2].chs.push_back(t1);
    ns[t1].deps++;
  }
  vector<int> bl_free;
  vector<int> wh_free;
  
  for(int i = 0; i < n; ++i) {
    if(ns[i].deps == 0) {
      if(ns[i].col) {
        wh_free.push_back(i);
      } else {
        bl_free.push_back(i);
      }
    }
  }

  int times = 0;
  while(!wh_free.empty() || !bl_free.empty()) {
    while(!wh_free.empty()) {
      int last = wh_free.back();
      wh_free.pop_back();
      for(int ch : ns[last].chs) {
        ns[ch].deps--;
        if(ns[ch].deps == 0) {
          if(ns[ch].col) {
            wh_free.push_back(ch);
          } else {
            bl_free.push_back(ch);
          }
        }
      }
    }

    bool sub_black = false;
    while(!bl_free.empty()) {
      sub_black = true;
      int last = bl_free.back();
      bl_free.pop_back();
      for(int ch : ns[last].chs) {
        ns[ch].deps--;
        if(ns[ch].deps == 0) {
          if(ns[ch].col) {
            wh_free.push_back(ch);
          } else {
            bl_free.push_back(ch);
          }
        }
      }
    }

    if(sub_black) times++;
  }

  cout << times << endl;
}

