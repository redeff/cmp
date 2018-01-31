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
  
  vector<pair<int, char>> ns;
  forn(i, 0, n) {
    ns.push_back(0, 0);
    cin >> ns.back().first >> ns.back().second;
  }
}

