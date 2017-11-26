#include "segtree.h"
#include <bits/stdc++.h>
using namespace std;

struct Op {
  Op(){}
  int op(int a, int b){
    return a + b;
  }

  int zero(){
    return 0;
  }
};

int main(){
  Segtree<int, Op> tree(16);
  cout << "lulu" << endl;
  tree.set(5, 1);
  tree.set(10, 1);
  tree.set(9, 1);
  tree.set(6, 1);
  tree.set(8, 1);
  tree.set(11, 1);
  for(int i: tree.tree){
    cout << i << " ";
  }
  cout << endl;
  cout << "lala" << endl;
  cout << tree.get(1, 10) << endl;
}

