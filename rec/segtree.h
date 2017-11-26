#include <bits/stdc++.h>
using namespace std;

int mid(int l, int r){
  return (l + r) / 2;
}

template<typename T> T next_power2(T value){
  --value;
  for(size_t i = 1; i < sizeof(T) * CHAR_BIT; i*=2)
    value |= value >> i;
  return value+1;
}

template <typename T, typename Op>
//Op must have a bool Op().op(T, T) fonction and a T Op().zero() function
class Segtree {
public:
  vector<T> tree;
  int n;

  T get_rec(int a, int b, int l, int r, int node){
    if(l >= a && r <= b){
      return tree[node];
    } else if (r <= a || l >= b){
      return Op().zero();
    } else {
      return Op().op(
          get_rec(a, b, l, mid(l, r), 2 * node + 1), 
          get_rec(a, b, mid(l, r), r, 2 * node + 2));
    }
  }

  void recalc(int node){
    tree[node] = Op().op(tree[2 * node + 1], tree[2 * node + 2]);
  }

public:
  T get(int a, int b){
    return get_rec(a, b, 0, n, 0);
  }

  void set(int index, T val){
    tree[n + index] = val;
    for(int i = (n + index - 1) / 2; i > 0; i = (i - 1) / 2){
      recalc(i);
    }
    recalc(0);
  }

  Segtree(int len){
    n = next_power2(len);
    tree = vector<T>(2 * n, Op().zero());
  }
};
