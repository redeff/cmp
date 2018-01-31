#include <bits/stdc++.h>
using namespace std;

#define BITS 8 
#define ROWS 3

int main() {
  int zero = 0;
  int topa = (1 << BITS) - 1;

  // unordered_set<int> all = {zero, 0b01000011, 0b10000000, 0b0011, 0b1001, 0b11000, topa};
  // unordered_set<int> all = {zero, 0b01000011, 0b10010000, 0b10000000, topa};
  unordered_set<int> all = {zero, 0b00101100, 0b01000011, 0b01101111, 1, topa};
  while(true) {
    unordered_set<int> nall;

    for(auto a : all) {
      nall.insert(a);
      nall.insert(topa ^ a);
      for(auto b : all) {
        nall.insert(a & b);
      }
    }

    if(nall == all) break;
    swap(all, nall);
  }

  for(int k = 0; k < 1 << (BITS - ROWS); ++k) {
    for(int i = zero; i <= topa; i += 1 << (BITS - ROWS)) {
      if(all.count(i + k) > 0) cout << "\033[31;1m";
      for(int b = BITS - 1; b >= 0; --b) cout << (((i + k) >> b) & 1);
      cout << "\033[0m";
      cout << "  ";
    }
    cout << endl;
  }
}
