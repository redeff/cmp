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

ll gets(ll a){
  if(a == 0) return 0;
  if(a < 4) return -1;
  if(a % 2 == 1) {
    ll rec = gets(a - 9);
    return rec == -1 ? -1 : rec + 1;
  }
  return a / 4;
}

int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n; ++i){
    ll tmp;
    cin >> tmp;
    cout << gets(tmp) << endl;
  }
}
