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
  int n, m;
  cin >> n >> m;
  vector<int> can(m, false);
  for(int i = 0; i < n; ++i){
    int a, b;
    cin >> a >> b;
    for(int j = a; j < b; ++j) {
      can[j] = true;
    }
  }

  for(int i = 0; i < m; ++i) {
    if(can[i] == false) {
      cout << "NO" << endl;
      return 0;
    }
  }
      cout << "YES" << endl;

}

