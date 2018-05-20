#include <bits/stdc++.h>
using namespace std;

int p(int n) {
  for(int i = 2; i * i <= n; ++i) {
    if(n % i == 0) return i;
  }
  return n;
}

const int BOUND = 20;

// Is n of the form x * x - x
int is_x2_x(int n)

int main() {
  for(int i = 2; i < BOUND; ++i) for(int j = 2; j < i; ++j) {
    if(i * i + j == p(i) + p(j) * p(j)) cout << i << " " << j << endl;
    else if(i * i + j > p(i) + p(j) * p(j)) cout << "MORE " << i << " " << j << endl;
    else cout << "LESS " << i << " " << j << endl;
  }
}
