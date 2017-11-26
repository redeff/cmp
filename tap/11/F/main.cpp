#include <bits/stdc++.h>
using namespace std;

struct Circ {
  int pos;
  int rad;

  Circ(int pos, int rad):
    pos(pos),
    rad(rad)
  {}
}

vector<Circ> get_costa(bool norte) {
  int n;
  cin >> n;
  vector<Circ> out;
  bool inside;
  {
    char temp;
    cin >> temp;
    inside = norte != (temp == 'N');
  }

  int pos = 0;
  for(int i = 0; i < n; ++i){
    int rad;
    cin >> rad;
    if(inside){
      out.push_back(Circ(pos + rad, rad));
    }
    pos += 2 * rad;
    inside = !inside;
  }

int main(){
  int a;


}
