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

struct Block {
  ll amount;
  ll pos;
  ll num;
  Block(int amount, int pos, int num): amount(amount), pos(pos), num(num) {}
  Block(){}
};

bool operator<(Block a, Block b) {
  if(a.amount == b.amount) return a.pos < b.pos;
  return a.amount > b.amount;
}

int main(){
  ll n;
  cin >> n;
  auto ns = get_vector<ll>(n);
  vector<Block> blocks;
  blocks.emplace_back(-1, -1, -1);
  forn(i, 0, n) {
    if(blocks.empty() || blocks.back().num != ns[i]) {
      blocks.emplace_back(1, i, ns[i]);
    } else {
      blocks.back().amount++;
    }
  }
  blocks.emplace_back(-1, -1, -1);

  map<Block, pair<Block, Block>> algo;

  forn(i, 0, blocks.size()) {
    algo.insert({blocks[i], {Block(-1, -1, -1), Block(-1, -1, -1)}});
  }

  forn(i, 1, blocks.size() - 1) {
    algo[blocks[i]].first = blocks[i - 1];
    algo[blocks[i]].second = blocks[i + 1];
  }

  int iters = 0;
  while(algo.size() > 2) {
    iters++;
    pair<Block, Block> p = (*algo.begin()).second;
    Block p_first = algo[p.first].first;
    Block p_second = algo[p.second].second;
    algo.erase(algo.begin());
    if(p.first.num == p.second.num) {
      algo.erase(algo.find(p.first));
      algo.erase(algo.find(p.second));
      auto nb = Block(p.first.amount + p.second.amount, p.first.pos, p.first.num);
      algo[nb] = make_pair(
          p_first, p_second
      );
      algo[p_first].second = nb;
      algo[p_second].first = nb;
    } else {
      algo[p.first].second = p.second;
      algo[p.second].first = p.first;
    }
  }

  cout << iters + 1 << endl;
}
