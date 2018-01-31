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

int main(){
  string s;
  cin >> s;

  int n = s.size();

  vector<pair<char, int>> blocks;
  for(int i = 0; i < n; ++i) {
    if(blocks.empty() || blocks.back().first != s[i]) {
      blocks.emplace_back(s[i], 1);
    } else {
      blocks.back().second++;
    }
  }

  int steps = 0;
  while(blocks.size() > 1) {
    steps++;
    // Decrease pass
    for(int i = 0; i < blocks.size(); ++i) {
      blocks[i].second -= 2;
    }
    blocks[0].second++;
    blocks[blocks.size() - 1].second++;

    // Delete pass
    {
      vector<pair<char, int>> nbs;
      for(int i = 0; i < blocks.size(); ++i) {
        if(blocks[i].second > 0) nbs.push_back(blocks[i]);
      }
      swap(blocks, nbs);
    }

    // Join pass
    {
      vector<pair<char, int>> nbs;
      for(int i = 0; i < blocks.size(); ++i) {
        if(nbs.empty() || nbs.back().first != blocks[i].first) {
          nbs.push_back(blocks[i]);
        } else {
          nbs.back().second += blocks[i].second;
        }
      }
      swap(blocks, nbs);
    }
  }

  cout << steps << endl;
}

