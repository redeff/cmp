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
  int h;
  cin >> h;
  auto hs = get_vector<int>((ll)h + 1);
  for(int i = 0; i < h; ++i) {
    if(hs[i] > 1 && hs[i + 1] > 1) {
      cout << "ambiguous" << endl;
      vector<int> a{0};
      vector<int> b{0};
      int curr_parent = 1;
      for(int x = 1; x < h + 1; ++x) {
        for(int y = 0; y < hs[x]; ++y) {
          a.push_back(curr_parent);
          b.push_back(curr_parent);
          if(x == i + 1 && y == 0) {
            b.back()--;
          }
        }
        curr_parent += hs[x];
      }

      for(auto ae : a) {
        cout << ae << " ";
      } cout << endl;
      for(auto ae : b) {
        cout << ae << " ";
      } cout << endl;
      return 0;
    }
  }

  cout << "perfect" << endl;

}

