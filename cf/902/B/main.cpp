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
  int n;
  cin >> n;
  vector<int> conn;
  for(int i = 0; i < n - 1; ++i) {
    conn.emplace_back();
    cin >> conn.back();
  }

  vector<int> cols;
  for(int i = 0; i < n; ++i) {
    cols.emplace_back();
    cin >> cols.back();
  }

  int total = 0;
  for(int i = 0; i < n - 1; ++i) {
    if(cols[i + 1] == cols[conn[i] - 1]) total ++;
  }

  cout << n - total << endl;

}

