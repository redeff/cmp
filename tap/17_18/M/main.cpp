#include <bits/stdc++.h>
using namespace std;

int main() {
  int xa, ya, xb, yb;
  cin >> xa >> ya >> xb >> yb;

  if(xa > xb) swap(xa, xb);
  if(ya > yb) swap(ya, yb);

  if(ya == yb) {
    swap(xa, ya);
    swap(xb, yb);
  }

  if(xa == xb) cout << 4 + 2 * (yb - ya + 1);
  else cout << 2 * (xb - xa + 1 + yb - ya + 1);
}
