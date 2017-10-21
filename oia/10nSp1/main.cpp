#include <bits/stdc++.h>
using namespace std;

struct Sumo {
  int a, b, c;
  int i;

  Sumo(int a, int b, int i):
    a(a),
    b(b),
    i(i)
  {}

  Sumo reverse() {
    return Sumo(b, a, n, i);
  }
}

int main() {
  int n;
  cin >> n;
  vector<Sumo> sumos(n, Sumo(0, 0, 0, 0));
  for(int i = 0; i < n; ++i){
    cin >> sumos[i].a >> sumos[i].b;
    sumos[i].i = i;
  }

  vector<Sumo> sorted_a = sumos;
  sort(sorted_a.begin(), sorted_a.begin(), [](Sumo s1, Sumo s2){
    if(s1.a < s2.a){
      return true;
    } else if(s1.a > s2.a) {
      return false;
    } else {
      return s1.b < s2.b;
    }
  });

  for(int i = 1; i < n; ++i) {
    if(sorted_a[i - 1].a == sorted_a[i].a && sorted_a[i - 1].b == sorted_a[i].b) {
      sorted_a[i].c = sorted_a[i - 1].c + 1;
    }
  }

  vector<int> sorted_b = vector<int>();
  for(int i = 0; i < n; ++i) {
    sorted_b.push_back(i);
  }
  sort(sorted_a.begin(), sorted_a.begin(), [&sorted_a] (int i1, int i2){
      Sumo s1 = sorted_a[i1];
      Sumo s2 = sorted_a[i2];
      if(s1.b < s2.b){
        return true;
      } else if(s1.b > s2.b) {
        return false;
      } else {
        if(s1.a < s2.a){
          return true;
      } else if(s1.a > s2.a){
        return false;
      } else {
        return s1.c < s2.c;
      }
        //return s1.a < s2.a;
      }
    });

  vector<int> out(n);
  set<int> in_a;
  for(int i = 0; i < n; ++i)




}
