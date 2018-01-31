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
  int a, b, c;
  cin >> a >> b >> c;

  if(a > c) swap(a, c);
  if(a > b) swap(a, b);
  if(b > c) swap(b, c);

  if(a == 3 && b == 3 && c == 3) {
    cout << "YES" << endl;
    return 0;
  }
  if(a == 2 && b == 2) {
    cout << "YES" << endl;
    return 0;
  }
  if(a == 1) {
    cout << "YES" << endl;
    return 0;
  }
  if(a == 2 && b == 4 && c == 4) {
    cout << "YES" << endl;
    return 0;
  }
  cout << "NO" << endl;
}

